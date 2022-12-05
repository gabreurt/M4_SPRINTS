const jogadorDaVez = document.querySelector(".jogadorDaVez"); //essa constante se conecta com o h2 do html

let url = "http://192.168.43.167/"; // ip do meu servidor com o esp32

let escolhido; // lugar escolhido pelo player
let player = "X"; // player atual

let positions = [ //posicoes possiveis de se ganhar
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
    [1, 4, 7],
    [2, 5, 8],
    [3, 6, 9],
    [1, 5, 9],
    [3, 5, 7],
];

function init() {
    escolhido = []; // array que guarda as jogadas escolhidas
    jogadorDaVez.innerHTML = `JOGADOR DA VEZ: ${player}`; // fala no html de quem é a vez 
    document.querySelectorAll(".game button").forEach((item) => { // seleciona o quadrante
        item.innerHTML = ""; // unsere o x ou o O
        item.addEventListener("click", novoTurno);
    });
}

init();

function novoTurno(e) {
    const index = e.target.getAttribute("data-i"); // index
    e.target.innerHTML = player; //Atribuímos a jogada realizada no quadrante.
    e.target.removeEventListener("click", novoTurno); // O clique neste campo não pode ser realizado de novo
    escolhido[index] = player; // vai preencher o X ou o O nos quadrados
    setTimeout(() => { // verifica se alguem ganhou
        check();
    }, [100]);
    player = player === "X" ? "O" : "X"; // fazemos o jogador variar entre X e O
    jogadorDaVez.innerHTML = `JOGADOR DA VEZ: ${player}`; // troca-se a vez do jogsdor  
}

function check() {
    let ultimaJogada = player === "X" ? "O" : "X"; // ve quem foi o ultimo a jogar

    const items = escolhido // verifica se a ultima jogada do jogador atual é a vitoriosa
        .map((item, i) => [item, i])
        .filter((item) => item[0] === ultimaJogada)
        .map((item) => item[1]);

    for (pos of positions) { // analisa posicoes vencedoras
        // caso a posicao vencedpra tenha sido alcancada
        if (pos.every((item) => items.includes(item))) {
            // se o vencedor foi o X, chama-se a função ganhou_x que acende o led azul
            if (ultimaJogada == "X") {
                ganhou_x();
            // se o vencedor foi o X, chama-se a função ganhou_x que acende o led vermelho
            } else if (ultimaJogada == "O") {
                ganhou_0();
            }
            // anuncia-se a vitoria do jogador e reinicia-se o jogo
        alert("PARABÉNS JOGADOR '" + ultimaJogada + "', VOCÊ GANHOU!");
            init();
            return;
        }
    }

    if (escolhido.filter((item) => item).length === 9) {
        // se empatar, o led amarelo se acende, anuncia-se o empate e reinicia o jogo
        empate();
        alert("DEU EMPATE!");
        init();
        return;
    }

        // requisicao que acende os leds  
    function ganhou_x() {
        $.ajax({
            url: url + "x_vencedor",
        })
    }

    function ganhou_0() {
        $.ajax({
            url: url + "o_vencedor",
        })
    }

    function empate() {
        $.ajax({
            url: url + "empate",
        })
    }
}