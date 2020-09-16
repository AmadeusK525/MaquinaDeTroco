  O executável versão release está na pasta vc_mswu. O programa foi completamente escrito (sem utilização de um IDE para "desenhar" a parte GUI) utilizando a biblioteca wxWidgets.
  
  Essa biblioteca não possui um int main(), a função principal está "mascarada" nos arquivos MyApp.h e MyApp.cpp, sendo a função OnInit() a euivalente à int main(). 
A biblioteca requer heap allocation, mas limpa a memória por si só utilizando uma hierarquia de janelas, então eu praticamente nunca uso 'delete' no programa, mas 
não há vazamento de memória. 
  
  O executável foi linkado estaticamente, então o arquivo deve funcionar por si só normalmente.
