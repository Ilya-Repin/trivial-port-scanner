# Trivial Port Scanner

Trivial Port Scanner - инструмент для сканирования TCP портов на различных хостах. 

- При помощи конфигурационного файла можно удобно настраивать сканирование для каждого хоста
- Для работы с сетью используется библиотека Boost.Asio
- Сканирование каждого хоста выполняется в собственном потоке.

## Инструкция:
1. **Установка и сборка:**
    ```shell
    mkdir build-release
    cd build-release
    pip3 install conan==1.*
    conan install .. --build=missing -s build_type=Release -s compiler.libcxx=libstdc++11
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --target all
    ```

2. **Настройка конфигурационного файла:**

    Описание конфигурационного файла [config.json](config.json):
    - `reports_dir`: Директория, в которой сохраняются отчеты о состоянии портов. По умолчанию называется `scanner_reports`
    - `hosts`: Список объектов с информацией о хостах, портах и диапазонах портов для сканирования.
        - `host`: адрес хоста.
        - `single_ports`: Список конкретных портов для сканирования.
        - `port_ranges`: Список диапазонов портов для сканирования на данном хосте.

   ### Пример конфигурационного файла:
    ```json
    {
      "reports_dir": "scanner_reports",
      "hosts": [
        {
          "host": "127.0.0.1",
          "single_ports": [22, 443, 8080],
          "port_ranges": [
            {
              "from": 100,
              "to": 110
            },
            {
              "from": 1120,
              "to": 1130
            }
          ]
        },
        {
          "host": "example.com",
          "single_ports": [1111, 2222, 3333],
          "port_ranges": [
            {
              "from": 110,
              "to": 120
            },
            {
              "from": 1000,
              "to": 1010
            }
          ]
        }
      ]
    }
    ```

3. **Запуск программы:**

    При запуске программы укажите расположение конфигурационного файла
    ```shell
    build-release/bin/trivial_port_scanner --config-file config.json
    ```
   Тесты можно запустить при помощи
    ```shell
    ctest --extra-verbose --test-dir build
    ```
