#!/bin/bash

# Основные переменные
user="skype"    # пользователь из под которого будет запускаться приложение
start_command="screen -d -m ~skype/megascript"    # программа, которая будет запускаться в фоне

if ( [ "$(whoami)" = "$user" ] ) then
        bash -c "$start_command"
else
        su -c "$start_command" -l $user
fi

