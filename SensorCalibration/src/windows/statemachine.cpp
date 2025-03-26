#include "statemachine.hpp"

void StateMachine::run()
{
    while (currentState != State::DONE)
    {
        processState();
    }
}

void StateMachine::processState()
{
    switch (currentState)
    {
    case State::INITIALIZATION:
        if (!uart.configureSerialPort() || !cnc.configureSerialPort())
        {
            std::cerr << "FATAL ERROR: Configure Port" << std::endl;
            currentState = State::DONE;
        }
        else
        {
            currentState = State::SETUP;
        }
        break;

    case State::SETUP:
        uart.writeToSerialPort(config.readString("Reference_sensor", "b1", "0") + " " +
                               config.readString("Reference_sensor", "b0", "0") + " " +
                               config.readString("Reference_sensor", "SampleSize", "5") + "\n");
        uart.serialToCout();
        uart.serialToCout();
        currentState = State::POSITIONING;
        break;

    case State::POSITIONING:
        if (position < 8)
        {
            cnc.moveOverToNext(position);
            samples = 0;
            currentState = State::SAMPLING;
        }
        else
        {
            currentState = State::CLEANUP;
        }
        break;

    case State::SAMPLING:
        performSampling();
        break;

    case State::LOGGING:
        logger << data.sampleNumber << " " << data.loadCellValue;
        for (const auto &val : data.fingerPositionValues)
        {
            logger << " " << val;
        }
        logger << "\n";
        samples++;
        currentState = State::SAMPLING;
        break;

    case State::CLEANUP:
        cnc.moveOverToNext(8);
        uart.writeToSerialPort("RESET\n");
        currentState = State::DONE;
        break;

    case State::DONE:
        break;
    }
}

void StateMachine::performSampling()
{
    if (samples < 10)
    {
        uart.writeToSerialPort("READY\n");
        std::string receivedData = uart.readFromSerialPort();
        SampleData data;
        if (parseSampleData(receivedData, data))
        {
            logger << data.sampleNumber << " " << data.loadCellValue;
            for (const auto &val : data.fingerPositionValues)
            {
                logger << " " << val;
            }
            logger << "\n";
        }
        samples++;
        cnc.moveRelative("Z", -0.1);
        Sleep(1000);
    }
    else
    {
        cnc.moveRelative("Z", 0.9);
        position++;
        currentState = State::POSITIONING;
    }
}

bool StateMachine::parseSampleData(const std::string &receivedData, SampleData &data)
{
    if (receivedData.empty())
    {
        return false;
    }

    std::istringstream strm(receivedData);
    if (!(strm >> data.sampleNumber >> data.loadCellValue))
    {
        return false; // check needed?
    }

    data.fingerPositionValues.resize(8);
    for (double &value : data.fingerPositionValues)
    {
        if (!(strm >> value))
        {
            return false;
        }
    }

    size_t pos = receivedData.find('C');
    if (pos != std::string::npos)
    {
        pos = receivedData.find('\n', pos);
        if (pos != std::string::npos)
        {
            std::string newData = receivedData.substr(pos + 1);
            std::istringstream strm2(newData);
            std::string CC, channel, datal[4];
            if (strm2 >> CC >> channel >> datal[0] >> datal[1] >> datal[2] >> datal[3])
            {
                logger << channel << " " << datal[0] << " " << datal[1] << " " << datal[2] << " " << datal[3] << "\n";
                std::cout << "Channel: " << channel << " b1:" << datal[0] << " b0:" << datal[1] << " r2:" << datal[2] << " se:" << datal[3] << std::endl;
            }
        }
    }
    return true;
}

void StateMachine::logSampleData()
{
    logger << data.sampleNumber << " " << data.loadCellValue;
    for (const auto &val : data.fingerPositionValues)
    {
        logger << " " << val;
    }
    logger << "\n";
    samples++;
    currentState = State::SAMPLING;
}
