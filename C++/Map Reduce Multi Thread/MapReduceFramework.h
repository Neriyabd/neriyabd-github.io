#ifndef MAPREDUCEFRAMEWORK_H
#define MAPREDUCEFRAMEWORK_H

#include "MapReduceClient.h"

typedef void* JobHandle;

enum stage_t {UNDEFINED_STAGE=0, MAP_STAGE=1, SHUFFLE_STAGE=2, REDUCE_STAGE=3};

/**
 * The JobState structure defines a data type that represents the stage
 * and percentage progress of a job.
 */
typedef struct {
	stage_t stage;
	float percentage;
} JobState;

/**
 adds a key-value pair to the intermediate vector of a thread in a thread-safe
 manner by locking a mutex, performing the necessary operations, and then
 unlocking the mutex.
 * @param key - pointer to key2
 * @param value - pointer to value2
 * @param context - threads context
 */
void emit2 (K2* key, V2* value, void* context);

/**
 * adds a key-value pair to the output vector in a thread-safe manner by
 * locking a mutex, appending the pair to the output vector, and then
 * unlocking the mutex.
 * @param key - pointer to key3
 * @param value - pointer to value3
 * @param context - threads context
 */
void emit3 (K3* key, V3* value, void* context);

/**
 *  initializes and starts a MapReduce job by creating a job object,
 *  threads, and other necessary resources. It sets up the job parameters,
 *  creates threads using pthread_create, and returns the created job handle.
 * @param client - client containing the map and reduce functions
 * @param inputVec - vector of key1 and value1
 * @param outputVec - empty vector to fill data
 * @param multiThreadLevel - number of threads in the program
 * @return - the job struct containing program's data
 */
JobHandle startMapReduceJob(const MapReduceClient& client,
	const InputVec& inputVec, OutputVec& outputVec,
	int multiThreadLevel);

/**
 * waits for the completion of all threads associated with a job by using
 * pthread_join to join each thread. It keeps track of whether waitForJob has
 * been called before to prevent duplicate waiting.
 * @param job - struct pointer to the program data
 */
void waitForJob(JobHandle job);

/**
 * The getJobState function extracts and calculates the job's stage
 * and percentage progress based on its atomic state.
 * @param job - struct pointer to the program data
 * @param state - a struct to fill percentage of stage and stage to
 */
void getJobState(JobHandle job, JobState* state);

/**
 * cleans up and releases resources associated with a MapReduce job,
 * including atomic counters, barriers, mutexes, vector pointers,
 * thread arrays, and the job object itself.
 * @param job - struct pointer to the program data
 */
void closeJobHandle(JobHandle job);
	
	
#endif //MAPREDUCEFRAMEWORK_H
