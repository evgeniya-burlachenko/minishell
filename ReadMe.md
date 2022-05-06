Проект по созданию своей оболочки для командной строки, поведение похоже на bash



#Brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
#if at school
curl -fsSl https://raw.githubusercontent.com/kube/42homebrew/master/install.sh | zsh

#readline
brew install readline

#if problem with brew
sudo mkdir /usr/local/Cellar
sudo chown -R $(whoami) /usr/local/Cellar

#check readline
brew info readline | head -1

************************************for evaluation:************************************

export PATH="check_path/1:check_path/2"

echo 123 > 42 | echo 321 >> 42 | cat 42 | grep 1 | wc -c

***************************************************************************************
