#ifndef OPENPOSE_UTILITIES_ERROR_AND_LOG_HPP
#define OPENPOSE_UTILITIES_ERROR_AND_LOG_HPP

#include <atomic>
#include <mutex>
#include <sstream> // std::stringstream
#include <string>
#include <vector>
#include <ctime> // std::tm, std::time_t
#include <fstream> // std::ifstream, std::ofstream
#include <iostream> // std::cout, std::endl
#include <stdexcept> // std::runtime_error

namespace crazy
{

#if ANDROID
template<typename T>
inline void error(const T& message, const int line = -1, const std::string& function = "", const std::string& file = "")
{

}
#else

enum class ErrorMode :  char
{
    StdRuntimeError,
    FileLogging,
    StdCerr,
    All,
};

enum class LogMode : unsigned char
{
    FileLogging,
    StdCout,
    All,
};

enum class Priority : unsigned char
{
    None = 0,
    Low = 1,
    Normal = 2,
    High = 3,
    Max = 4,
    NoOutput = 255,
};

enum class DataFormat : unsigned char
{
    Json,
    Xml,
    Yaml,
    Yml,
};


template<typename T>
std::string tToString(const T& message)
{
    // Message -> ostringstream
    std::ostringstream oss;
    oss << message;
    // ostringstream -> std::string
    return oss.str();
}

// Error managment - How to use:
// error(message, __LINE__, __FUNCTION__, __FILE__);

std::string getTime();
void error(const std::string& message, const int line = -1, const std::string& function = "", const std::string& file = "");

template<typename T>
inline void error(const T& message, const int line = -1, const std::string& function = "", const std::string& file = "")
{

    error(tToString(message), line, function, file);

//        std::string fileToOpen{"crazy_3dmm_Log_error.txt"};
//
//        // Get current file size
//        std::ifstream in{fileToOpen, std::ios::binary | std::ios::ate};
//        const auto currentSizeBytes = in.tellg();
//        in.close();
//
//        // Continue at the end of the file or delete it and re-write it (according to current file size)
//        const auto maxLogSize = 15 * 1024 * 1024; // 15 MB
//        std::ofstream loggingFile{fileToOpen, (currentSizeBytes < maxLogSize ? std::ios_base::app : std::ios_base::trunc)};
//
//        // Message to write
//        loggingFile << getTime();
//        loggingFile << "\n";
//        loggingFile << tToString(message) <<" "<<function << " "<<file;
//        loggingFile << "\n\n\n\n\n";
//
//        loggingFile.close();


}

// Printing info - How to use:
// log(message, desiredPriority, __LINE__, __FUNCTION__, __FILE__);  // It will print info if desiredPriority >= sPriorityThreshold
void log(const std::string& message, const Priority priority = Priority::Max, const int line = -1, const std::string& function = "", const std::string& file = "");

template<typename T>
inline void log(const T& message, const Priority priority = Priority::Max, const int line = -1, const std::string& function = "", const std::string& file = "")
{
    log(tToString(message), priority, line, function, file);
}

// If only desired on debug mode (no computational cost at all on release mode):
// dLog(message, desiredPriority, __LINE__, __FUNCTION__, __FILE__);  // It will print info if desiredPriority >= sPriorityThreshold
template<typename T>
inline void dLog(const T& message, const Priority priority = Priority::Max, const int line = -1, const std::string& function = "", const std::string& file = "")
{
#ifndef NDEBUG
    log(message, priority, line, function, file);
#else
    //    UNUSED(message);
    //    UNUSED(priority);
    //    UNUSED(line);
    //    UNUSED(function);
    //    UNUSED(file);
#endif
}

// This class is thread-safe
class  ConfigureError
{
public:
    static std::vector<ErrorMode> getErrorModes();

    static void setErrorModes(const std::vector<ErrorMode>& errorModes);
};

// This class is thread-safe
class  ConfigureLog
{
public:
    static Priority getPriorityThreshold();

    static const std::vector<LogMode>& getLogModes();

    static void setPriorityThreshold(const Priority priorityThreshold);

    static void setLogModes(const std::vector<LogMode>& loggingModes);
};

#endif
}


#endif // OPENPOSE_UTILITIES_ERROR_AND_LOG_HPP
