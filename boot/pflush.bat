for /f "tokens=* usebackq" %%i IN (`ptcstatus -nopause ^| sed -e 's/[^[:print:][:space:]]//g' -e 's/ \+/ /g' ^| grep -i 'mecha-sever'`) do @echo %%i
