#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdlib>
#include <cmath>

struct Pixel {
    int r, g, b;
};

// Convierte tu matriz a una imagen de OpenCV
cv::Mat aImagen(const std::vector<std::vector<Pixel>>& matriz) {
    int alto = matriz.size();
    int ancho = matriz[0].size();

    cv::Mat img(alto, ancho, CV_8UC3);

    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            const Pixel& p = matriz[i][j];
            img.at<cv::Vec3b>(i, j) = cv::Vec3b(p.b, p.g, p.r);  // BGR
        }
    }
    return img;
}

int main() {
    int alto = 120, ancho = 160;
    std::vector<std::vector<Pixel>> matriz(alto, std::vector<Pixel>(ancho, {0, 0, 0}));

    for (int j = 0; j < ancho; ++j)
    {
        matriz[alto - 1][j] = {225, 225, 225}; //la candela (fuel)
    }

    while (true) {

        for(int i = 0; i<alto - 1; i++)
        {
            for(int j = 0; j<ancho; j++)
            {
                int decay = rand() % 4;
                int xs = j + (rand() % 3) - 1;
                xs = std::clamp(xs, 0, ancho - 1);

                const Pixel& src = matriz[i + 1][xs];
                matriz[i][j].r = std::max(0, src.r - decay);
                matriz[i][j].g = std::max(0, src.g - decay * 2);
                matriz[i][j].b = std::max(0, src.b - decay * 3);
            }
        }

        cv::Mat frame = aImagen(matriz);
        cv::imshow("Video", frame);
        if (cv::waitKey(1000/170) == 27) break;
    }
    return 0;
}