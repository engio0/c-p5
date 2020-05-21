@FOR /f "tokens=*" %%G IN ('WHERE %1') DO @PUSHD "%%~dpG"
