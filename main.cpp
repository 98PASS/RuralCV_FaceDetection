#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat original;
Mat imagem_em_processo;
vector<Rect> areas_de_interesse; //vetor de retangulos que guarda áreas de interesse da imagem lida

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
    if(imagem_em_processo.empty()){
       imagem_em_processo = original.clone();
    }
    Mat amostra = imagem_em_processo.clone();
    putText(amostra, nome_etapa, Point(5, 25), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(255, 90, 255), 2);
    imshow("Detecção Facial", amostra);
};

//FUNÇÃO que equaliza a intensidade luminosa
Mat equalizaIntensidade()
{
        Mat ycrcb;
        cvtColor(original, ycrcb, CV_BGR2YCrCb); //converte de bgr para ycrcb
        vector<Mat> canais;
        split(ycrcb, canais); //separa os canais no vetor
        equalizeHist(canais[0], canais[0]); //equaliza o histograma do canal de luminância
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

//FUNÇÃO que separa os tons de pele do resto da imagem
Mat detecar_pele(){
    imagem_em_processo = novo_sistema_de_cor();
    Mat resultado;
    Mat binbin;
    inRange(imagem_em_processo,Scalar(0,133,77),Scalar(235,173,127),binbin);
    bitwise_and(imagem_em_processo,imagem_em_processo,resultado,binbin);
    return resultado;
}

//FUNÇÃO que segmenta com o threshold OSU (baseado em variancia)
Mat segmentar(){
    imagem_em_processo = detecar_pele();
    Mat resultado;
    Mat blur;
    GaussianBlur(imagem_em_processo,blur,Size(5,5),0);
    threshold(blur,blur,THRESH_BINARY,255,0);
    threshold(blur,resultado,THRESH_OTSU,255,0);
    return resultado;
}

//FUNÇÃO que agrupa os pixels em elementos distintos
Mat candidatos_de_face(){
    imagem_em_processo = segmentar();
    vector<Mat> canais;
    split(imagem_em_processo,canais);//separa em canais
    Mat imagem_em_processo = canais[0]; //pega apenas o primeiro canal
    Mat imagem_rotulada(imagem_em_processo.size(), CV_32S); //cria matriz do tamanho da imagem em processo
    int nRotulos = connectedComponents(imagem_em_processo, imagem_rotulada, 8);
    std::vector<Vec3b> colors(nRotulos);
    colors[0] = Vec3b(0, 0, 0);//background em preto
    for(int rotulo = 1; rotulo < nRotulos; ++rotulo){
        colors[rotulo] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255) ); // cada componente recebe uma cor rgb randomica
    }
    Mat resultado(imagem_em_processo.size(), CV_8UC3);
    for(int r = 0; r < resultado.rows; ++r){
        for(int c = 0; c < resultado.cols; ++c){
            int rotulo = imagem_rotulada.at<int>(r, c);
            Vec3b &pixel = resultado.at<Vec3b>(r, c);
            pixel = colors[rotulo];
        }
    }


    Mat componente; //imagem com um único componente
    vector<vector<Point>> contours;

    for(int i=1;i<colors.size();i++){ //Loop que cria retangulos em torno dos objetos de interesse da imagem

       inRange(resultado, colors[i], colors[i], componente);
       Rect retangulito =  boundingRect(componente);
       //condicional do retangulo
       if(retangulito.height > 13 && retangulito.width > 13 /*&& retangulito.size().area() <= (original.size().area()*0.75)*/){
           areas_de_interesse.insert(areas_de_interesse.end(),retangulito);
           rectangle(resultado,retangulito,Scalar(0,255,0),4);
       }
    }

    return resultado;
}

//FUNÇÃO que seleciona o maior grupo de pixels
Mat olhos_e_boca(){
    Mat resultado;
    vector<Mat> dimensoes;
    Mat mapaCrominancia_olhos; //Mapa de olhos da crominancia
    Mat mapaLuminancia_olhos; //Mapa de olhos da luminancia

    split(equalizaIntensidade(), dimensoes);//separo a imagem original em canais diferentes


    //Normalizações e operações
    Mat Y,Cb,Cr;
    Y = dimensoes[0];
    Cr = dimensoes[1];
    Cb = dimensoes[2];
    normalize(Cr, Cr,  0, 1, NORM_MINMAX, CV_32F);
    normalize(Cb, Cb,  0, 1, NORM_MINMAX, CV_32F);

//  Componentes da fórmula de mapa de olhos de crominancia
    Mat notCr2 = 255 - Cr;
    notCr2 = notCr2.mul(notCr2); // = not Cr²
    Mat Cb2 = Cb.mul(Cb); // Cb²
    Mat  divCbCr = Cb / Cr;
    //
    normalize(Cb2, Cb2,  0, 1, NORM_MINMAX, CV_32F);
    normalize(notCr2, notCr2, 0, 1, NORM_MINMAX, CV_32F);
    normalize(divCbCr, divCbCr, 0, 1, NORM_MINMAX, CV_32F);

    mapaCrominancia_olhos = (Cb2 + notCr2 + divCbCr) / 3; // fórmula aplicada

//

//    imshow("mapa",mapaCrominancia_olhos);
//    imshow("notCr2",notCr2);
//    imshow("Cb2", Cb2);
//    imshow("divCbCr",divCbCr);
//    imshow("Y",dimensoes[0]);
//    imshow("Cr",dimensoes[1]);
//    imshow("Cb",dimensoes[2]);

//Preciso adicionar retangulos de interesse de olhos e boca à variável global
    return original;
}

//FUNÇÃO que destaca os limites da face na imagem original
Mat limites_da_face(){
    //esta função depende da função anterior
    imagem_em_processo = olhos_e_boca();
    Mat resultado = imagem_em_processo.clone();
    for (int i = 0; i < areas_de_interesse.size(); ++i) {
        rectangle(resultado,areas_de_interesse[i],Scalar(0,255,0),3);
    }
    return  resultado;
    //preciso remover os triangulos que na parte de dentro não possuem os triangulos de interesse de olhos e boca
}

//FUNÇÃO callback que mapeia a entrada da trackbar para a função referente do processo da detecção
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
            imagem_em_processo = detecar_pele();
            break;
        case 4://segmentação baseada em variância
            imagem_em_processo = segmentar();
            break;
        case 5://compomentes conexos e agrupamento
            imagem_em_processo = candidatos_de_face();
            break;
        case 6://detecção de olhos e boca
            imagem_em_processo = olhos_e_boca();
            break;
        case 7://detecção de limites da face
            imagem_em_processo = limites_da_face();
            break;
        case 8://verificando/pesando triangulacao olhos/boca
            break;

    }
    exibir(nome_etapa);
}

int main(){
    original = imread("imagensTeste/Imagens/humans2.jpg");
    namedWindow("Detecção Facial",WINDOW_NORMAL);
    createTrackbar("Etapa: ", "Detecção Facial", &etapa, 8, funcSlider_etapas);
    exibir(get_etapa(0));
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


    while(1){ //loop até fechar o programa
        char c = waitKey(1);
        if( c == 'q' || c=='Q'){
            break;
        }
    }

    destroyAllWindows();
    return 0;
}
