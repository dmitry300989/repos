// EventTracing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <strsafe.h>
#include <evntprov.h>
#include <evntrace.h>
#include <cassert>

// GUID that identifies your trace session.
// Remember to create your own session GUID.

// {AE44CB98-BD11-4069-8093-770EC9258A12}
static const GUID SessionGuid =
{ 0xae44cb98, 0xbd11, 0x4069, { 0x80, 0x93, 0x77, 0xe, 0xc9, 0x25, 0x8a, 0x12 } };

struct EventTracePropertiesWithBuffers {
    EventTracePropertiesWithBuffers(const GUID& sessionId, std::string logFilePath) {
        ::ZeroMemory(this, sizeof(EventTracePropertiesWithBuffers));

        Properties.Wnode.BufferSize = sizeof(EventTracePropertiesWithBuffers);
        Properties.LoggerNameOffset = offsetof(EventTracePropertiesWithBuffers, SessionName);
        Properties.LogFileNameOffset = offsetof(EventTracePropertiesWithBuffers, LogFilePath);

        Properties.Wnode.Flags = WNODE_FLAG_TRACED_GUID;
        Properties.Wnode.ClientContext = 1; //QPC clock resolution

         // For private session, use the Provider's id instead of a unique session ID.
        Properties.Wnode.Guid = sessionId;

        // See: https://docs.microsoft.com/en-us/windows/win32/etw/logging-mode-constants
        Properties.LogFileMode =
            EVENT_TRACE_FILE_MODE_SEQUENTIAL
            | EVENT_TRACE_PRIVATE_LOGGER_MODE
            | EVENT_TRACE_PRIVATE_IN_PROC;

        SetLogFilePath(logFilePath);
    }

    void SetLogFilePath(std::string logFilePath) {
        std::copy(logFilePath.begin(), logFilePath.end(), std::begin(LogFilePath));
    }

    EVENT_TRACE_PROPERTIES Properties;
    char SessionName[256]; // Arbitrary max size for the buffer, but 1024 is the system limit.
    char LogFilePath[1024]; // Max supported filename length is 1024
};

int main()
{
    // Initialized to random GUID with CoCreateGuid() 
    GUID providerId;
    ::CoCreateGuid(&providerId);

    // Provider's handle. Unregister with EventUnregister() later.
    REGHANDLE providerHandle;

    // Registering the provider
    ::EventRegister(&providerId, nullptr, nullptr, &providerHandle);

    const char* sessionName = "My unique log session name";

    // Event session information
    EventTracePropertiesWithBuffers eventTraceproperties(SessionGuid, "trace.etl");

    // properties initialization code (skipped, see below) ...

    // Stop later with: ControlTrace with 
    // ControlCode = EVENT_TRACE_CONTROL_STOP.
    TRACEHANDLE sessionHandle;

    // Starts the trace, copies sessionName into buffer 
    // whose offset is specified in properties's structure.
    ::StartTraceA(&sessionHandle, sessionName, &eventTraceproperties.Properties);

    ::EnableTraceEx2(
        sessionHandle,
        &providerId,
        EVENT_CONTROL_CODE_ENABLE_PROVIDER,
        TRACE_LEVEL_INFORMATION,
        0,
        0,
        0,
        NULL
    );

    // Our message
    std::vector<uint8_t> message;

    // Event descriptor. 
    // We don't really use any of the fields here.
    constexpr static const EVENT_DESCRIPTOR c_descriptor = {
        0x1,    // Id
        0x1,    // Version
        0x0,    // Channel
        0x0,    // LevelSeverity
        0x0,    // Opcode
        0x0,    // Task
        0x0,    // Keyword
    };

    EVENT_DATA_DESCRIPTOR eventDataDescriptors[1];
    EventDataDescCreate(&eventDataDescriptors[0], message.data(), static_cast<ULONG>(message.size()));

    ::EventWrite(providerHandle, &c_descriptor, 1, eventDataDescriptors);

    ::EnableTraceEx2(
        sessionHandle,
        &providerId,
        EVENT_CONTROL_CODE_DISABLE_PROVIDER,
        TRACE_LEVEL_INFORMATION,
        0,
        0,
        0,
        NULL
    );

    ::ControlTraceA(sessionHandle, sessionName, &eventTraceproperties.Properties, EVENT_TRACE_CONTROL_STOP);

    ::EventUnregister(providerHandle);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
