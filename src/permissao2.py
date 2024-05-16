def vcEhOQue(grafoDeNomes):
    for key in grafoDeNomes:
        if len(grafoDeNomes[key]) % 2 == 0:
            grafoDeNomes[key] = "ADM"
        else:
            grafoDeNomes[key] = "Usuário"
    
    return grafoDeNomes
        
    
nomes = {
    "Roberto": "ShaolinMatadorDePorcos",
    "Claudio": "Função",
    "Ludmila": "Cuzinho rosa",
    "Marcus Vinicius": "Arrombado",
    "Rafael Ivo": "Cu mais aberto que uma rodela",
    "Anderson Feitoza": "Pre treino de café e punheta"
}


funcoes = {}
funcoes = vcEhOQue(nomes)
print(funcoes)