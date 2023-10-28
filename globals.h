//
// Created by shkit on 26.10.2023.
//

#pragma once
//
// Created by shkit on 26.10.2023.
//


/*
 * Глобальные переменные суммируются в процессе моделирования. Они необходимы для итоговой статистики
 */
extern int num_korabl;// количество кораблей
//для нахождения средней длины очереди
extern int global_count_queue;
extern int global_len_queue;

//для нахождения максимальной задержки разгрузки
extern int max_duration;

//время ожидания в очереди
extern int global_sum_time_queue;
extern int global_len_time_queue;

// средняя задержка разгрузки
extern int sum_duration;
extern int len_duration;

//общая сумма штрафа
extern int all_penny;

