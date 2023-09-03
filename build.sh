echo Compiling program
g++ main.cpp -o build/server.out

echo Creating folders
mkdir ./build/html
mkdir ./build/scripts

echo Creating config files
touch ./build/routes.conf
touch ./build/script-routes.conf
touch ./build/config.conf
