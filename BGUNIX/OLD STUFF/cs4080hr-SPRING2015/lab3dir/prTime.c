
char * prTime()
{
        static char buf[80];
        time_t timeval;
        time(&timeval);
        strncpy(buf, ctime(&timeval), 24);

        return buf;
}

