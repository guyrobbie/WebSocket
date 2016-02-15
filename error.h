#ifndef _ERROR_H_
#define _ERROR_H_

//extern void error(char *msg);

inline void error(char *msg)
{
    perror(msg);
    exit(0);
}

#endif /* #ifndef _ERROR_H_ */