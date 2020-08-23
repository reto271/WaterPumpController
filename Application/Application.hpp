#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#ifdef __cplusplus
extern "C" {
#endif

void initializeBackgroundLoop();
void ApplicationTimerInterrupt10ms();
void runBackgroudLoop();

#ifdef __cplusplus
}
#endif

#endif // __APPLICATION_HPP__
