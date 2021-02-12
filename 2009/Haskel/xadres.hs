----------------------------------------------------------------------------------------------
-- PROG FUNCIONAL E COMP SIMBOLICA [turma 06N] -----------------------------------------------
----------------------------------------------------------------------------------------------
-- ANTONIO LUIZ BASILE -----------------------------------------------------------------------
----------------------------------------------------------------------------------------------
-- EP - Xadrez em notação Forsyth ------------------------------------------------------------
----------------------------------------------------------------------------------------------
-- DANILO RIBEIRO   3060233-5 ----------------------------------------------------------------
-- HELTON ISAC      3068645-8 ----------------------------------------------------------------
-- RENATO PEDROSA   3062961-6 ----------------------------------------------------------------
----------------------------------------------------------------------------------------------
-- 	Escreva um programa em Haskell que recebe uma descrição de um tabuleiro de -----------
-- Xadrez em notação Forsyth (abaixo) e responde com as descrições  do  tabuleiro, -----------
-- também  em  notação  Forsyth,  de  todas as possíveis jogadas das peças brancas -----------
-- (apenas a próxima jogada).                                                      -----------
----------------------------------------------------------------------------------------------



--Execute a seguinte função para verificar os movimentos iniciais
--retornaMovimentosBranca inicio



--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--função principal que retorna uma lista contendo outras listas representando todas as jogadas
--possíveis para as peças brancas
retornaMovimentosBranca lista = percorre (converte lista)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Cadeia de entrada indicando inicio de jogo
inicio = "tcbdrbct-pppppppp-8-8-8-8-PPPPPPPP-TCBDRBCT"
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Transforma o tabuleiro em uma unica string para facilitar os movimentos
--converte deste formato...: "tcbdrbct-pppppppp-8-8-8-8-PPPPPPPP-TCBDRBCT"
--para este formato........: "tcbdrbctppppppppXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXPPPPPPPPTCBDRBCT" 
converte [] = [] 
converte (a:x) | a == '-' = converte x 
	       | verificaBrancaPreta a = a:(converte x)
	       | otherwise = transformaNemX (cint a)++(converte x)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Transforma os numeros que estao na String em 'X'
transformaNemX 0 = []
transformaNemX n = 'X':(transformaNemX (n - 1))
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Verifica se e uma peca branca ou preta
verificaBrancaPreta a = (verificaBranca a) || (verificaPreta a)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Verifica se é uma peça branca
verificaBranca a = (a == 't' || a == 'c' || a == 'b' || a == 'd' || a == 'r' || a == 'p')
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Verifica se é uma peça preta
verificaPreta a = (a == 'T' || a == 'C' || a == 'B' || a == 'D' || a == 'R' || a == 'P')
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--converte um numero de char para int
cint a | a == '1' = 1
       | a == '2' = 2
       | a == '3' = 3
       | a == '4' = 4
       | a == '5' = 5
       | a == '6' = 6
       | a == '7' = 7
       | a == '8' = 8
       | otherwise = 0
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--converte um numero de int para char
cstr a | a == 1 = '1'
       | a == 2 = '2'
       | a == 3 = '3'
       | a == 4 = '4'
       | a == 5 = '5'
       | a == 6 = '6'
       | a == 7 = '7'
       | a == 8 = '8'
       | otherwise = '0'
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--converte deste formato...: "tcbdrbctppppppppXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXPPPPPPPPTCBDRBCT" 
--para este formato........: "tcbdrbct-pppppppp-8-8-8-8-PPPPPPPP-TCBDRBCT"
desconverte l = tXN (divideString l)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Recebe uma string no seguinte formato  : "tcbdrbctppppppppXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXPPPPPPPPTCBDRBCT" 
--e retorna a mesma com divisão de linhas: "tcbdrbct-pppppppp-XXXXXXXX-XXXXXXXX-XXXXXXXX-XXXXXXXX-PPPPPPPP-TCBDRBCT"
divideString l = divideStringAux l 0
divideStringAux [] n = []
divideStringAux (a:x) n | n < 8 = a:(divideStringAux x (n + 1))
		        | otherwise = ('-'):(divideStringAux (a:x) 0)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Substitui as ocorrencias de X para o numero das ocorrencias por linha e grupo de X
tXN l = tXNaux l 0

tXNaux  [] n | n == 0 = []
	     | otherwise =  (cstr n):[]
tXNaux (a:x) n | a == 'X' = (tXNaux x (n+1))
	       | n == 0 = a:(tXNaux x 0)
	       | otherwise = (cstr n):a:(tXNaux x 0)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Percorre retornando os movimentos disponiveis para cada peca
percorre l = limpaVazias (percorreAux l l 1)

percorreAux [] l n = []
percorreAux (a:x) l n | verificaBranca a = (movimenta a (poeX n l) n)++(percorreAux x l (n+1))
		      | otherwise = percorreAux x l (n+1)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Tira as cadeias vazias
limpaVazias [] = []
limpaVazias (a:x) | a == [] = limpaVazias x
		  | otherwise = a:limpaVazias x

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Seleciona o movimento que sera realizado
movimenta a tab n | a == 't' = movimentaTorre tab n 't'
		  | a == 'c' = movimentaCavalo tab n
		  | a == 'b' = movimentaBispo tab n 'b'
		  | a == 'd' = movimentaDama tab n
		  | a == 'r' = movimentaRei tab n
		  | a == 'p' = movimentaPeao tab n
		  | otherwise = []
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Indica o limite do tabuleiro
limitesTab n | n > 0 && n < 9 = (1,8)
   	     | n > 8 && n < 17 = (9,16)
	     | n > 16 && n < 25 = (17,24)
	     | n > 24 && n < 33 = (25,32)
	     | n > 32 && n < 41 = (33,40)
	     | n > 40 && n < 49 = (41,48)
	     | n > 48 && n < 57 = (49,56)
	     | n > 56 && n < 65 = (57,64)
	     | otherwise = (-500,-500)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Movimentos da torre
--chamada principal do movimento
movimentaTorre l n p = (movToAux1 l (n-1) (limitesTab n) p) ++ 
                       (movToAux2 l (n+1) (limitesTab n) p) ++ 
		       (movToAux3 l (n-8) p) ++ 
                       (movToAux4 l (n+8) p)


--movimenta Torre Auxiliar, recebe a lista com o tabuleiro sem a peca que se deseja mover, um numero indicando onde a peca estaria
--e uma dupla indicando os limites verticais do tabuleiro naquela linha
movToAux1 l n (a,b) p | n < a = []
		      | verificaBranca (verificaPosicaoN l n) = []
		      | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
		      | otherwise = (desconverte (subItemLista n l p)):(movToAux1 l (n-1) (a,b) p)

movToAux2 l n (a,b) p | n > b = []
		      | verificaBranca (verificaPosicaoN l n) = []
		      | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
		      | otherwise = (desconverte (subItemLista n l p)):(movToAux2 l (n+1) (a,b) p)

--Recebe a lista com o tabuleiro sem a peca que se deseja mover e o numero indicando onde ela estaria                     
movToAux3 l n p | n < 1 = []
	        | verificaBranca (verificaPosicaoN l n) = []
	        | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	        | otherwise = (desconverte (subItemLista n l p)):(movToAux3 l (n-8) p)

movToAux4 l n p | n > 64 = []
	        | verificaBranca (verificaPosicaoN l n) = []
	        | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	        | otherwise = (desconverte (subItemLista n l p)):(movToAux4 l (n+8) p)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Movimentos do Cavalo
--Recebe a lista com o tabuleiro sem o cavalo que esta se tentando mover e um numero indicando sua posicao no tabuleiro
movimentaCavalo l n = (movCaAux l (n + 17) (limitesTab (n+16))) ++ (movCaAux l (n - 17) (limitesTab (n-16))) ++ 
		      (movCaAux l (n + 15) (limitesTab (n+16))) ++ (movCaAux l (n - 15) (limitesTab (n-16))) ++ 
		      (movCaAux l (n + 10) (limitesTab (n+ 8))) ++ (movCaAux l (n - 10) (limitesTab (n- 8))) ++ 
                      (movCaAux l (n +  6) (limitesTab (n+ 8))) ++ (movCaAux l (n - 6 ) (limitesTab (n- 8))) 

--Recebe a lista com o tabuleiro sem o cavalo que esta se tentando mover, um numero indicando a posicao que se deseja preencher
--e os limites da linha desejada para validar se esta inserindo na linha correta
movCaAux l n (a,b) | n < a || n > b = []
             	   | verificaBranca (verificaPosicaoN l n) = []
	           | otherwise = [desconverte (subItemLista n l 'c')]
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--movimentos do Bispo 
--Recebe a lista com o tabuleiro sem o bispo que esta se tentando mover e um numero indicando sua posicao no tabuleiro
movimentaBispo l n p = (movBiAux1 l (n - 9) (limitesTab (n-8)) p) ++ (movBiAux2 l (n - 7) (limitesTab (n-8)) p) ++
		       (movBiAux3 l (n + 9) (limitesTab (n+8)) p) ++ (movBiAux4 l (n + 7) (limitesTab (n+8)) p)

--Recebe a lista com o tabuleiro sem o bispo que esta se tentando mover, um numero indicando a posicao que se deseja preencher
--e os limites da linha desejada para validar se esta inserindo na linha correta
movBiAux1 l n (a,b) p | n < a || n > b = []
                      | verificaBranca (verificaPosicaoN l n) = []
	              | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	              | otherwise = desconverte (subItemLista n l p):(movBiAux1 l (n-9) (limitesTab (n-8)) p)

movBiAux2 l n (a,b) p | n < a || n > b = []
                      | verificaBranca (verificaPosicaoN l n) = []
	              | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	              | otherwise = desconverte (subItemLista n l p):(movBiAux2 l (n-7) (limitesTab (n-8)) p)

movBiAux3 l n (a,b) p | n < a || n > b = []
                      | verificaBranca (verificaPosicaoN l n) = []
	              | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	              | otherwise = desconverte (subItemLista n l p):(movBiAux3 l (n+9) (limitesTab (n+8)) p)

movBiAux4 l n (a,b) p | n < a || n > b = []
                      | verificaBranca (verificaPosicaoN l n) = []
	              | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l p)]
	              | otherwise = desconverte (subItemLista n l p):(movBiAux4 l (n+7) (limitesTab (n+8)) p)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Movimentos da Dama
--Combinação dos movimentos da Torre e do Bispo
movimentaDama l n = (movimentaBispo l n 'd') ++ (movimentaTorre l n 'd')
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Movimentos do Rei
movimentaRei l n = (movReiAux l (n-1) (limitesTab n)) ++ (movReiAux l (n+1) (limitesTab n)) ++
                   (movReiAux l (n-7) (limitesTab (n-8))) ++ (movReiAux l (n-8) (limitesTab (n-8))) ++ (movReiAux l (n-9) (limitesTab (n-8))) ++
                   (movReiAux l (n+7) (limitesTab (n+8))) ++ (movReiAux l (n+8) (limitesTab (n+8))) ++ (movReiAux l (n+9) (limitesTab (n+8)))

movReiAux l n (a,b) | n < a || n > b = []
                    | verificaBranca (verificaPosicaoN l n) = []
                    | verificaPreta (verificaPosicaoN l n) = [desconverte(subItemLista n l 'r')]
	            | otherwise = [desconverte (subItemLista n l 'r')]

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Movimentos do Peão
movimentaPeao l n = (movPeaofrente l (n+8) (limitesTab (n+8))) ++
                    (movPeaoCome   l (n+7) (limitesTab (n+8))) ++
                    (movPeaoCome   l (n+9) (limitesTab (n+8))) ++
                    (movPeaoPriJog l  n (limitesTab 16))

movPeaofrente l n (a,b) | n < a || n > b = []
                        | verificaBranca (verificaPosicaoN l n) = []
                        | verificaPreta  (verificaPosicaoN l n) = []
                        | otherwise = [desconverte(subItemLista n l 'p')]

movPeaoCome l n (a,b) | n < a || n > b = []
                      | verificaBranca (verificaPosicaoN l n) = []
                      | verificaPreta  (verificaPosicaoN l n) = [desconverte(subItemLista n l 'p')]
                      | otherwise = []

movPeaoPriJog l n (a,b) | n < a || n > b = []
                        | verificaBranca (verificaPosicaoN l (n+8)) || verificaBranca (verificaPosicaoN l (n+16)) = []
                        | verificaPreta  (verificaPosicaoN l (n+8)) || verificaPreta  (verificaPosicaoN l (n+16)) = []
                        | otherwise = [desconverte(subItemLista (n+16) l 'p')]


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Retorna um item na lista em uma determinada posicao
verificaPosicaoN (a:x) n | n == 1 = a
			 | otherwise = verificaPosicaoN x (n-1)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Tira a peca que esta tentando mover e substitui por X
poeX 1 (a:x) = 'X':x
poeX n (a:x) = a:(poeX (n-1) x)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--Substitui um item na lista em uma determinada posicao
subItemLista 1 (a:x) new = new:x
subItemLista n (a:x) new = a:(subItemLista (n-1) x new)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

