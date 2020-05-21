@dir *%1* /b | awk -F[._] "{print $1}" | uniq
