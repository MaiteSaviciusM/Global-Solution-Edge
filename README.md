# Controle de Estoque de Medicamentos com DHT, Sensor Ultrassônico e ESP32

Este projeto é uma simulação de um sistema de controle de estoque de medicamentos usando um DHT, um sensor ultrassônico HC-SR04 e um microcontrolador ESP32 na plataforma de simulação Wokwi. O código aqui presente permite monitorar o nível de medicamentos em um recipiente com base na distância medida pelo sensor ultrassônico.

*PillGuardian*

A solução PillGuardian foi pensada para simplificar a rotina das pessoas que
necessitam administrar múltiplos medicamentos diariamente. Seu propósito principal é
oferecer um sistema de gerenciamento confiável e seguro, proporcionando uma
autonomia controlada e indispensável aos usuários. Ao exigir uma senha para editar
informações ou acessar os medicamentos e doses antes do horário preestabelecido, a
PillGuardian assegura que apenas as doses corretas sejam liberadas no momento
apropriado, evitando assim erros ou situações de risco.

Essa solução surge não apenas como uma ferramenta de conveniência para os
clientes, mas também como uma medida fundamental de segurança e prevenção. O foco
na autonomia do usuário vai de encontro à necessidade de garantir que a administração
de medicamentos seja realizada de maneira precisa, sem riscos de confusões ou
ingestões inadequadas, principalmente para crianças ou idosos. A prevenção de erros ou
acidentes é um pilar essencial da PillGuardian, buscando oferecer tranquilidade e
confiança aos usuários, bem como aos seus familiares e cuidadores.

Ao fornecer um sistema automatizado e seguro, a PillGuardian visa não apenas
simplificar, mas também revolucionar a experiência de gerenciamento de
medicamentos, promovendo uma abordagem precisa e segura para a adesão ao
tratamento, enquanto alivia o fardo diário dos usuários e reduz o risco de ocorrência de
erros associados à administração dos medicamentos.

*O problema*

O tópico escolhido foi "Melhoria geral da saúde : prevenção de abuso de substâncias" 

Em 2021, dos 91.883 casos de intoxicação relacionados a produtos sujeitos à
vigilância sanitária, impressionantes 79,7% representaram incidentes associados a
medicamentos, totalizando 74.123 ocorrências. Esse número reflete uma preocupação
significativa quanto à administração inadequada ou errônea de medicamentos,
evidenciando a necessidade crítica de medidas que assegurem a precisão e a segurança
na ingestão de medicamentos. 

Nesse contexto, soluções inovadoras como a PillGuardian se destacam como
recursos essenciais. Ao oferecer um sistema automatizado de administração de
medicamentos, a PillGuardian não apenas simplifica o processo, mas também estabelece
camadas adicionais de segurança, exigindo autenticação para liberar doses e
monitorando o ambiente interno onde os medicamentos são armazenados.
Essa abordagem proativa não só reduz os riscos de overdoses acidentais, mas
também promove uma administração precisa e controlada de medicamentos,
contribuindo significativamente para a prevenção de erros e a segurança dos usuários.

Configuração do ambiente
- Abra a plataforma de simulação Wokwi
- Selecione a opção  "ESP32" e "HTTP Server"
- Selecione os Sensores DHT (Sensor de temperatura e umidade) e HC-SR04 (Sensor Ultrassônico): 
- DHT
    - GND - Conectado ao GND (terra) do ESP32
    - VCC - Conectado ao pino 3V3 do ESP32
    - SDA - Conectado a um pino digital do ESP32 (por exemplo, GPIO32)
- HC-SR04
    - VCC - Conectado ao pino 5V do ESP32
    - GND - Conectado ao GND (terra) do ESP32
    - TRIGGER - Conectado a um pino digital do ESP32 (por exemplo, GPIO21)
    - ECHO - Conectado a um pino digital do ESP32 (por exemplo, GPIO22)
Certifique-se de configurar as conexões conforme mencionado no código e adapte caso necessário.

Bibliotecas Necessárias

Este código utiliza as bibliotecas ArduinoJson.h, DHTesp.h e EspMQTTClient para comunicação MQTT com o Tago.io. Certifique-se de adiconá-las à Wokwi antes de compilar o código.

Funcionamento

O código lê a distância medida pelo sensor ultrassônico e calcula a quantidade de medicamentos no recipiente com base nessa distância (considerando que cada medicamento possui um tamanho de 0,5 cm). 

    Distância padrão: 40cm (0 comprimidos)
    Distância com metade da capacidade: 20cm (40 comprimidos)
    Distância com capacidade total: 0cm (80 comprimidos)

Em seguida, determina o estado do estoque (cheio, intermediário ou vazio) de acordo com os limites de distância predefinidos. Além disso, ele publica os dados no Tago.io por meio de MQTT para monitoramento remoto. Lá, foram cadastrados avisos sobre o estoque e condições do ambiente que possam arriscar os medicamentos. Essas, extraídas de bulas de medicamentos reais. 

Configuração da Tago.io

O código está configurado para se conectar ao Tago.io e enviar os dados de quantidade de medicamentos. Certifique-se de fornecer as credenciais corretas (nome e token do dispositivo) no código para permitir a comunicação com seu servidor MQTT do Tago.io.

*Links*

Wokwi: https://wokwi.com/projects/382230131121758209

Vídeo Explicativo: https://youtu.be/En4NYHMRRmQ


MAITÊ SAVICIUS RM98435
MURILO OBINATA RM99855
