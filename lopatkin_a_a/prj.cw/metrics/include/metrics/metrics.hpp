/*!
* @mainpage Метрики оценки качества бинаризации
* 
* Разработал: Лопаткин Антон Алексеевич. Студент 1-го курса группы БПМ-22-1
*/

/*!
* @file metrics.hpp
* @brief Заголовочный файл с объявлением функций для расчета метрик.
*/

#pragma once
#ifndef METRICS_HPP
#define METRICS_HPP

#include <opencv2/core.hpp>

/*!
* @brief Вычисляет метрику Distance-Reciprocal Distortion (DRD)
* @param[in] img_GT - эталонное изображение (Ground Truth)
* @param[in] img_bin - бинаризованное изображение, такого же размера как и Ground Truth
* @param[in] m - сторона квадратной матрицы весов
* @param[in] n - сторона блока для вычисления NUBN 
*/
double DRD(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin, int m = 5, int n = 8);

/*!
* @brief Вычисляет Misclassification penalty metric (MPM)
* @param[in] img_GT - эталонное изображение (Ground Truth)
* @param[in] img_bin - бинаризованное изображение, такого же размера как и Ground Truth
*/
double MPM(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin);

/*!
* @brief Вычисляет F-Measure
* @param[in] img_GT - эталонное изображение (Ground Truth)
* @param[in] img_bin - бинаризованное изображение, такого же размера как и Ground Truth
*/
double FMeasure(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin);

/*!
* @brief Вычисляет метрику Peak-Signal-to-Noise-Ratio (PSNR)
* @param[in] img_GT - эталонное изображение (Ground Truth)
* @param[in] img_bin - бинаризованное изображение, такого же размера как и Ground Truth
*/
double PSNR(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin);

#endif