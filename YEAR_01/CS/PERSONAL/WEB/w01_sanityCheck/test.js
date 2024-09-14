window.onload = function() {
  document.getElementById("ID").onclick = function() {
    // Logica qui, o alternativamente assegna la funzione al gestore dell'evento
  };

  /* ... */
};

// Sintassi alternativa | Arrow functions
window.onload = () => {
  document.getElementById("ID").onclick = () => {
    // ...
  };

  /* ... */
};

function test() {console.log("TEST");}