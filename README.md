# cpp-delaunay-algorithm

1. arquivo de pontos do espaço separados em linhas e cols (vindas do C)
2. arquivo passa para aquele vetor com a normal e as triangulações
  2.1 le toda a terceira coluna do arquivo e ordena de forma decrescente
  2.1 desce o scan começando de z = +inf e para em z = 0 a partir de 2.1
  2.2 na leitura de pelo menos 3 pontos, fazer análise da propriedade de arcos
    2.2.1 descrever uma circunferencia que inclua os 3 pontos
    2.2.2 verificar se algum ponto até então encontrado no scan pertence a essa circunferencia
  2.3 se não há nenhum ponto, o triangulo é aceito no conjunto triangulação (pro STL depois)
    2.3.1 no plano, se não há ponto implica que não há solução real para a coordenada do "4 ponto do quadrilátero" cujo angulo da diagona é pi