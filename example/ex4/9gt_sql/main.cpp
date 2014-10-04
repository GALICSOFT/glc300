


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_i30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif

#include <stdio.h>
#include <ac/sqlite3.h>


int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for( i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
};


int main(int argc, char** argv)
{
	sqlite3 *pSQLite3 = NULL;	
	char    *szErrMsg = NULL;

	int rst = sqlite3_open( "test.db", &pSQLite3);

	if ( rst )
	{
		printf( "Can't open database: %s\n", sqlite3_errmsg( pSQLite3 ));

		sqlite3_close( pSQLite3 );
		pSQLite3 = NULL;
	}
	else
	{
		printf("Database opened!!\n");

		rst = sqlite3_exec(pSQLite3, "CREATE TABLE member ( name TEXT(20), age INTEGER )", callback, 0, &szErrMsg);
		rst = sqlite3_exec(pSQLite3, "INSERT INTO member ( name, age ) values ( 'andy', 20 )", callback, 0, &szErrMsg);
		rst = sqlite3_exec(pSQLite3, "SELECT * FROM member", callback, 0, &szErrMsg);
	}

	sqlite3_free( szErrMsg );
	sqlite3_close( pSQLite3 );
	
	return 0;
}