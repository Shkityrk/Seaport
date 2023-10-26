//
// Created by shkit on 26.10.2023.
//


/*
 * Глобальные переменные суммируются в процессе моделирования. Они необходимы для итоговой статистики
 */
int num_korabl=0;// количество кораблей
//для нахождения средней длины очереди
int global_count_queue=0;
int global_len_queue=0;

//для нахождения максимальной задержки разгрузки
int max_duration=0;

//время ожидания в очереди
int global_sum_time_queue=0;
int global_len_time_queue=0;

// средняя задержка разгрузки
int sum_duration=0;
int len_duration=0;

//общая сумма штрафа
int all_penny=0;