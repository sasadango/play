#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int discriminantAnalysis(cv::Mat_<uchar> src, cv::Mat_<uchar>& dst) {
    /* ヒストグラム作成 */
    std::vector<int>hist(256, 0);
    for (int y=0; y < src.rows; y++) {
        for (int x=0; x < src.cols; x++) {
            hist[static_cast<int>(src(y, x))]++;
        }
    }

    /* 判別分析法 */
    int t = 0;
    double max = 0.0;

    for (int i=0; i < 256; i++) {
        int w1 = 0; // クラス１の画素数
        int w2 = 0; // クラス２のがぞ数
        long sum1 = 0; // クラス１の合計画素
        long sum2 = 0; // クラス２の合計画素
        double m1 = 0.0; // クラス１の平均値
        double m2 = 0.0; // クラス２の平均

        for (int j=0; j <=i; j++) {
            w2 += hist[j];
            sum2 += j * hist[j];
        }

        if (w1)
            m1 = (double)sum1 / w1;

        if (w2)
            m2 = (double)sum2 / w2;

        double tmp = ((double)w1*w2*(m1-m2)*(m1-m2));

        if (tmp > max) {
            max = tmp;
            t = i;
        }
    }

    /* tの値を使って２値化 */
    for (int y=0;y<src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            if (src(y, x) < t)
                dst(y, x) = 0;
            else
                dst(y, x) = 255
        }
    }
    return t
}

int main() {
    cv::Mat_<uchar> src = cv::imread("image.jpg", 0); // グレースケールで画像読み込み
    cv::Mat_<uchar> src2 = cv::imread("image.jpg", 0);

    int a = cv::threshold(src, src, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    int b = discriminantAnalysis(src2, src2);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
}