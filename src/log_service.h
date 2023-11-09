#ifndef SRC_LOG_SERVICE_H_
#define SRC_LOG_SERVICE_H_

enum LOGLEVEL
{
	LOG_LEVEL_NONE,
	LOG_LEVEL_ERROR,     // error
	LOG_LEVEL_WARNING,   // warning
	LOG_LEVEL_DEBUG,     // debug
	LOG_LEVEL_INFO,      // info	
};

enum LOGTARGET
{
	LOG_TARGET_NONE      = 0x00,
	LOG_TARGET_CONSOLE   = 0x01,
	LOG_TARGET_FILE      = 0x10
};

// 单例模式
class LogService {
    // 初始化
	void init(LOGLEVEL loglevel, LOGTARGET logtarget);
 
	// 
	void uninit();
 
	// file
	int CreateFile();
 
	static LogService* GetInstance();
 
	// Log级别
	LOGLEVEL get_loglevel();
	void set_loglevel(LOGLEVEL loglevel);
 
	// Log输出位置
	LOGTARGET get_logtarget();
	void set_logtarget(LOGTARGET logtarget);
 
	// 打log
	static int WriteLog(
		LOGLEVEL loglevel,         // Log级别
		unsigned char* fileName,   // 函数所在文件名
		unsigned char* function,   // 函数名
		int lineNumber,            // 行号
		char* format,              // 格式化
		...);                      // 变量
 
	// 输出log
	static void OutputToTarget();
};


#endif // SRC_LOG_SERVICE_H_