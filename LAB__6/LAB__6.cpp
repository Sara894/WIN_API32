#include <windows.h>

#include <iostream>

#include <Lmcons.h>

#include <VersionHelpers.h>

const char* GetOsVersionName()

{

	if (IsWindows10OrGreater())

	{

		return "10.0";

	}

	if (IsWindows8Point1OrGreater())

	{

		return "8.1";

	}

	if (IsWindows8OrGreater())

	{

		return "8";

	}

	if (IsWindows7OrGreater())

	{

		return "7";

	}

	if (IsWindowsVistaOrGreater())

	{

		return "Vista";

	}

	if (IsWindowsXPOrGreater())

	{

		return "XP";

	}

	return "Unknown";

}

BOOL CALLBACK EnumCodePagesProc(LPTSTR lpCodePageString)

{

	std::wcout << lpCodePageString << "\n";

	return TRUE;

}

int main()

{
	setlocale(LC_ALL, "Russian");
	std::cout << "Вариант 8. Лабораторная номер 6. Операционные системы." << "\n";

	// Пункт 1, получение имени компьютера и пользователя

	char compname[MAX_COMPUTERNAME_LENGTH + 1];

	char username[UNLEN + 1];

	DWORD compsize = sizeof(compname);

	DWORD usernamesize = sizeof(username);

	GetComputerNameA(compname, &compsize);

	GetUserNameA(username, &usernamesize);

	// Пункт 2, получение системных директорий

	char systemdirectory[256];

	char windowsdirectory[256];

	char tempdirectory[256];

	UINT systemdirectory_size = 256;

	UINT windowsdirectory_size = 256;

	DWORD tempdirectory_size = 256;

	GetSystemDirectoryA(systemdirectory, systemdirectory_size);

	GetWindowsDirectoryA(windowsdirectory, windowsdirectory_size);

	GetTempPathA(tempdirectory_size, tempdirectory);

	// Пункт 3, получение версии ОС

	const char* osVersion = GetOsVersionName();

	// Пункт 4, получение системных метрик

	int monitor_numbers = GetSystemMetrics(SM_CMONITORS);

	int monitor_width = GetSystemMetrics(SM_CXSCREEN);

	int monitor_height = GetSystemMetrics(SM_CYSCREEN);

	// Пункт 5, получение системных параметров
	//Извлекает информацию о функции специальных возможностей FilterKeys.
	//Параметр pvParam должен указывать на структуру FILTERKEYS, 
	//которая получает информацию. Задайте для члена cbSize этой структуры и параметра uiParam значение

	BOOL GETFILTERKEYS;

	//	Получает высоту в пикселях прямоугольника, внутри которого должен оставаться указатель мыши, 
	// чтобы TrackMouseEvent сгенерировал сообщение WM_MOUSEHOVER. 
	//Параметр pvParam должен указывать на переменную UINT, которая получает высоту.
	BOOL GETMOUSEHOVERHEIGHT;

	SystemParametersInfoA(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &GETFILTERKEYS, 0);

	SystemParametersInfoA(SPI_GETMOUSEHOVERHEIGHT, 0, &GETMOUSEHOVERHEIGHT, 0);
	
	std::cout << "______________________________Константы uiAction_______________________" << "\n";

	std::cout << "GETFILTERKEYS : " << GETFILTERKEYS << "\n";

	std::cout << "GETMOUSEHOVERHEIGHT: " << GETMOUSEHOVERHEIGHT << "\n";

	//Получает информацию о функции специальных возможностей StickyKeys. 
	// Параметр pvParam должен указывать на структуру STICKYKEYS, которая получает информацию. 
	//Задайте для члена cbSize этой структуры и параметра uiParam значение
	BOOL GETSTICKYKEYS;

	SystemParametersInfoA(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &GETSTICKYKEYS, 0);

	std::cout << "GETSTICKYKEYS: " << GETSTICKYKEYS << "\n";

	//Примечание  Если используется флаг SPI_SETDESKWALLPAPER,
	//	SystemParametersInfo возвращает значение TRUE,
	//	если нет ошибки(например, если указанный файл не существует).
	BOOL SETDESKWALLPAPER;
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, &SETDESKWALLPAPER, 0);
	std::cout << "SETDESKWALLPAPER: " << SETDESKWALLPAPER << "\n";

	//Включает или выключает обтекание значка заголовком.
	//Параметр uiParam указывает TRUE для включения или FALSE для отключения.
	BOOL SETICONTITLEWRAP;
	SystemParametersInfoA(SPI_SETICONTITLEWRAP, 0, &SETICONTITLEWRAP, 0);
	std::cout << "SETICONTITLEWRAP: " << SETICONTITLEWRAP << "\n";

	//Включает или отключает функцию «Следы мыши», 
	//которая улучшает видимость движений курсора мыши, 
	//кратко отображая следы курсоров и быстро стирая их. Чтобы отключить эту функцию,
	//  установите для параметра uiParam значение 0 или 1. Чтобы включить эту функцию, 
	//установите для uiParam значение больше 1, чтобы указать количество курсоров, нарисованных в следе.
	BOOL SETMOUSETRAILS;
	SystemParametersInfoA(SPI_SETMOUSETRAILS, 0, &SETMOUSETRAILS, 0);
	std::cout << "SETMOUSETRAILS: " << SETMOUSETRAILS << "\n";

	// Пункт 6, определение и изменение цветов

	DWORD border_color;

	DWORD border_color_new;

	const int lpaElements[1] = { COLOR_MENU };

	DWORD original_color[1] = { RGB(240,240,240) };

	DWORD new_color[1] = { RGB(51, 102, 255) };

	SetSysColors(1, lpaElements, original_color);

	border_color = GetSysColor(lpaElements[0]);

	SetSysColors(1, lpaElements, new_color);

	border_color_new = GetSysColor(lpaElements[0]);

	SetSysColors(1, lpaElements, original_color);

	// Пункт 7, функции для работы со временем

	SYSTEMTIME systemtime;

	SYSTEMTIME localtime;

	GetSystemTime(&systemtime);

	GetLocalTime(&localtime);

	// Пункт 8, дополнительные API функции

	// EnumSystemCodePages, GetInputState, GetLastError, SetKeyboardState

	BOOL inputstate;
	//Определяет, есть ли сообщения кнопки мыши или клавиатуры в очереди сообщений вызывающего потока

	inputstate = GetInputState();

	DWORD lasterror;
	//Извлекает значение кода последней ошибки вызывающего потока.
	//Код последней ошибки сохраняется для каждого потока отдельно.
	//Несколько потоков не перезаписывают код последней ошибки друг друга.
	lasterror = GetLastError();

	BYTE keystate[256];
	//Копирует состояние 256 виртуальных ключей в указанный буфер.
	GetKeyboardState(keystate);

	keystate['A'] = 1;

	//Копирует массив состояний клавиш клавиатуры в таблицу состояний ввода клавиатуры вызывающего потока.
	//Это та же таблица, к которой обращаются функции GetKeyboardState и GetKeyState.
	//Изменения, внесенные в эту таблицу, не влияют на ввод с клавиатуры в любой другой поток.

	SetKeyboardState(keystate);

	// Вывод результатов
	std::cout << "______________________________Вывод результатов_______________________" << "\n";

	std::cout << "Имя компутера: " << compname << "\n";

	std::cout << "Имя юзера : " << username << "\n";

	std::cout << "Системная папка : " << systemdirectory << "\n";

	std::cout << "Папка винды : " << windowsdirectory << "\n";

	std::cout << "Папка с шаблонами : " << tempdirectory << "\n";

	std::cout << "Версия операционной системы виндоус  " << osVersion << "\n";

	std::cout << "Метрики. __________________________________________________________" << "\n";

	std::cout << "Числа монитора : " << monitor_numbers << "\n";

	std::cout << "Разрешение монитора : " << monitor_width << "x" << monitor_height << "\n";
	std::cout << "Параметры системы . _______________________________________________" << "\n";

	

	std::cout << "Цвет меню RGB : " << "R: " << (int)GetRValue(border_color) << " G: " << (int)GetGValue(border_color) << " B: " << (int)GetBValue(border_color) << "\n";

	std::cout << "Измененный цвет меню в RGB: " << "R: " << (int)GetRValue(border_color_new) << " G: " << (int)GetGValue(border_color_new) << " B: " << (int)GetBValue(border_color_new) << "\n";

	std::cout << "Системное время : " << systemtime.wHour << ":" << systemtime.wMinute << "\n";

	std::cout << "Местное время : " << localtime.wHour << ":" << systemtime.wMinute << "\n";

	std::cout << "Входное состояние : " << inputstate << "\n";

	std::cout << "Код последней ошибки: " << lasterror << "\n";

	system("pause");

	std::cout << "Установленные кодовые страницы в системе" << "\n";
	//Перечисляет кодовые страницы, которые либо установлены, либо поддерживаются операционной системой.

	EnumSystemCodePages(EnumCodePagesProc, CP_INSTALLED);

}