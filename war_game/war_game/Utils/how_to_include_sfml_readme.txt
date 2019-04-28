Якщо проект не запускається тому, що не може знайти additional include library(include підкреслює), тоді:
1)Вибираємо в проекті зверху project -> war_game Properties.
2)Там configuration: Debug, Platform: x64.
3)Вибираємо в меню нижче C/C++ там клікаємо на поле additional include directories щоб його змінити (стрілочка вниз, Edit).
4)Вписуємо в поле зверху ваш персональний шлях до sfml251\include в проекті war_game. Тиснемо ОК.
5)Переходимо в меню до Linker там General i в полі additional library directories так само як і в кроці №3 вказуємо шлях АЛЕ тепер до sfml251\lib.
6)Зберігаємо і перезбираємо проект.