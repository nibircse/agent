/**
 *  @brief     KAThread.h
 *  @class     KAThread.h
 *  @details   KAThread Class is designed to handle executions.
 *  		   Each Execution runs concurrently and does the given command job.
 *  @author    Emin INAL
 *  @author    Bilal BAL
 *  @version   1.0
 *  @date      Aug 29, 2013
 *  @copyright GNU Public License.
 */
#ifndef KATHREAD_H_
#define KATHREAD_H_
#include <pthread.h>
#include <list>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "KAUserID.h"
#include "KACommand.h"
#include "KAConnection.h"
#include "KAResponsePack.h"
#include "KAStreamReader.h"
#include "KALogger.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::pthread;
using namespace boost::interprocess;
using namespace boost;

class KAThread
{
public:
	KAThread();
	virtual ~KAThread();
	bool threadFunction(message_queue*,KACommand*,char*[]);			//Execute command concurrently
	bool checkCWD(KACommand*);
	bool checkUID(KACommand*);
	string createExecString(KACommand*);
	int toInteger(string*);
	KAUserID& getUserID();
	KAResponsePack& getResponse();
	static string getProcessPid(const char*);
	KALogger& getLogger();
	void setLogger(KALogger);
	typedef struct numbers
	{
		int *responsecount;
		int *processpid;
		bool *flag;
		KALogger *logger;
	};
	static void taskTimeout(message_queue*,KACommand*,int*,string*,string*,struct numbers*,KALogger*);
	static void capture(message_queue*,KACommand*,KAStreamReader*,mutex*,string*,string*,struct numbers*,KALogger*);
	static void checkAndWrite(message_queue*,KAStreamReader*,string*,string*,KACommand*,struct numbers*,KALogger*);
	static void checkAndSend(message_queue*,KAStreamReader*,string*,string*,KACommand*,struct numbers*,KALogger*);
	static void lastCheckAndSend(message_queue *,KACommand*,string*,string*,struct numbers*,KALogger*);
	int optionReadSend(message_queue*,KACommand*,KAStreamReader*,KAStreamReader*,int);
	static string toString(int);
private:
	KAUserID uid;
	pid_t pid;
	KAResponsePack response;
	string argument,exec,sendout,environment;
	uid_t euid, ruid;
	KALogger logger;
};
#endif /* KATHREAD_H_ */
