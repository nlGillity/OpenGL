### Инструкция по сборке
Скачать на компьютер `git`, если его нет. Все действия будут производиться через командную строку `cmd`.
 - Для наглядности перейти в папку Рабочего стола
 <code>cd Desktop</code>
  - Скачать репозиторий:
 <code>git clone https://github.com/nlGillity/OpenGL</code>
  *На рабочем столе появится папка  OpenG*
 - Перейти в папку OpenGL: <code>cd OpenGL</code>
 - Подключение библиотек:
	 - Перейти в папку libs: <code>cd libs</code>
	 - Очистить пустые папки:  <code>rm -r glfw && rm -r glm</code>
	 - Скачаем библиотеку GLFW:
		 - <code>git clone https://github.com/glfw/glfw</code>
		 - `cd glfw`
		 - `cmake -S . -B build`
		 - `cmake --build build`
		 
		 *Для скачивания следующией библиотеку выйдем из данной папк*и `cd ..`
	- Скачаем библиотеку GLM:
		- <code>git clone https://github.com/g-truc/glm</code>
		- `cd glm`
		- `cmake \
    -DGLM_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -B build .`
	    - `cmake --build build -- all`
	    - Для выполения этой команды (возможно всё будет работать и без неё) могут потребваться права администратора: 
	    `cmake --build build -- install` 
	   
	- Библиотека GLAD уже есть, поэтому скачивать её не будем
	- УБЕДИТЬСЯ в том, что ВСE библиотеки находятся в папке libs!
 - Вернёмся в папку OpenGL: `cd ../..`
 - Удалим папку build: `rm -r build`
 - Подготовим проект к компиляции: `cmake -S . -B build`
 - Скомпилируем проект: `cmake --build build`
 *Тепперь в папке build находится исполняемый файл* `App.exe`
 - Запускать программу нужно строго из папки OpenGL, иначе main.cpp не найдет шейдеры:
	`.\build\App.exe` (в случае ошибки можно заменить на обратные слешы: `./build/App.exe` )
