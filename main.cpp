#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat original;
Mat imagem_em_processo;
int etapa=0;

Mat novo_sistema_de_cor(Mat mat);

//FUNÇÃO que retorna a string referente à etapa da imagem no processo;
std::string get_etapa(int n){
    std::string retorno = "";
    switch (n) {
        case 0:
            retorno = "Original";
            break;
        case 1:
            retorno = "Compensar Luminosidade";
            break;
        case 2:
            retorno = "Transf. do Sistema de Cores";
            break;
        case 3:
            retorno = "Detectar Tom de Pele";
            break;
        case 4:
            retorno = "Segmentar Baseado em Variancia";
            break;
        case 5:
            retorno = "Componentes Conexos e Agrupamento";
            break;
        case 6:
            retorno = "Detectar de Olhos e Boca";
            break;
        case 7:
            retorno = "Detectar de Limites da Face";
            break;
        case 8:
            retorno = "Verificando/Pesando Triangulo Olhos->Boca";
            break;
    }
    return retorno;
}

//FUNÇÃO que exibe a imagem
void exibir(std::string nome_etapa){
    Mat amostra = imagem_em_processo.clone();
    putText(amostra, nome_etapa, Point(5, 25), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(255, 0, 255), 2);
    imshow("Imagem", amostra);
};

//FUNÇÃO que equaliza a intensidade luminosa
Mat equalizaIntensidade()
{
        Mat ycrcb;
        cvtColor(original, ycrcb, CV_BGR2YCrCb); //converte de bgr para ycrcb
        vector<Mat> canais;
        split(ycrcb, canais); //separa os canais no vetor
        equalizeHist(canais[0], canais[0]); //equaliza o histograma de cada canal
        Mat resultado;
        merge(canais, ycrcb); //Junta os canais equalizados na imagem ycrcb
        cvtColor(ycrcb, resultado, CV_YCrCb2BGR); //passa o resultado para rgb

        return resultado;

}

//FUNÇÃO que muda o sistema de cor de RGB para YCbCr
Mat novo_sistema_de_cor() {

    imagem_em_processo = equalizaIntensidade();
    Mat resultado;
    cvtColor(imagem_em_processo,resultado,CV_BGR2YCrCb);
    return resultado;
}

void funcSlider_etapas(int, void *){
    string nome_etapa = get_etapa(etapa);
    cout << "Etapa: " << etapa << " - " << nome_etapa << std::endl;
    switch (etapa) {
        case 0://original
            imagem_em_processo = original.clone();
            break;
        case 1://compensação luminosa
            imagem_em_processo = equalizaIntensidade();
            break;
        case 2://transformação do espaço de cores
            imagem_em_processo = novo_sistema_de_cor();
            break;
        case 3://detecção de tons de pele
            break;
        case 4://segmentação baseada em variância
            break;
        case 5://compomentes conexos e agrupamento
            break;
        case 6://detecção de olhos e boca
            break;
        case 7://detecção de limites da face
            break;
        case 8://verificando/pesando triangulacao olhos/boca
            break;

    }
    exibir(nome_etapa);
}

int main(){
    namedWindow("Imagem",WINDOW_NORMAL);
    createTrackbar("Etapa: ", "Imagem", &etapa, 8, funcSlider_etapas);
    /* Mostra a etapa do algoritmo de reconhecimento
     * Etapas:
     * 1. Imagem Original
     * 2. Compensação Luminosa
     * 3. Transformação do Espaço de Cores
     * 4. Detecção de Cor de Pele
     * 5. Segmentação Baseada em Variância
     * 6. Componentes Conexos & Agrupamento
     * 7. Detecção de Olhos e Boca
     * 8. Detecção de Limites da Face
     * 9. Verificando/Pesando Triângulos de Olhos e Boca
     */
    original = imread("imagensTeste/Imagens/human2.jpg");
    imshow("Imagem", original);

    while(1){ //loop principal
        char c = waitKey(1);
        if( c == 'q' || c=='Q'){
            break;
        }
    }
    destroyAllWindows();
    return 0;
}
