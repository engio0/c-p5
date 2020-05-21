@ECHO OFF
IF [%1]==[] (
        ECHO Usage: ptckick username ^| * ^| all
        GOTO:EOF
        )

SETLOCAL
IF [%1]==[*] SET _names=PROE_EssentialsII.*7788
IF [%1]==[all] SET _names=PROE_EssentialsII.*7788
SET _names=%1

FOR /f "usebackq tokens=1-5" %%i IN (`ptcstatus -nopause ^| grep -i '%_names%.*PROE_EssentialsII'`) DO (
      ECHO Kicking out %%i...  ptcflush %%j %%k %%l %%m 
      @ ptcflush %%j %%k %%l %%m > NUL
   )
ENDLOCAL
