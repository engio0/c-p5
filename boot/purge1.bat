@CALL purge %1 %2 %3 %4
@FOR /f "usebackq" %%i IN (`  DIR /B ^| grep -P "[.][0-9]{1,}$" ^| grep -v "[.]1$"  `) DO (
		RENAME %%i %%~ni.1
		ECHO %%i   ^>^>^>   %%~ni.1 )
