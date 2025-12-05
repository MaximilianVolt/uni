/*:
 * @plugindesc Sistema di reclutamento casuale con pesi e premi alternativi se già in gruppo.
 * @author Tu
 *
 * @help
 * Plugin Command:
 *   RecruitRandomActor <RIMBORSO> <PESI> (metasintassi)
 *   RecruitRandomActor 125 [8,4,2,1]
 *
 * Oppure senza argomenti:
 *   RecruitRandomActor
 */

(function() {
  function cw(a) {
    let n = Math.random() * a.reduce((acc, val) => acc + val, 0);

    for (let i = 0; i < a.length; n -= a[i++])
      if (n < a[i])
        return i;

    return a.length - 1;
  }

  const c = [
    // ID personaggi comuni
    [2, 3, 4, 6, 9, 10, 33, 34, 35, 37, 45, 49, 67],

    // ID personaggi rari
    [5, 11, 12, 13, 26, 39, 69, 70, 71, 79],

    // ID personaggi epici
    [7, 18, 21, 23, 42, 46, 47, 72],

    // ID personaggi chimerici
    [25, 30, 57, 64],
  ];

  const _Game_Interpreter_pluginCommand = Game_Interpreter.prototype.pluginCommand;
  Game_Interpreter.prototype.pluginCommand = function(command, args) {
    _Game_Interpreter_pluginCommand.call(this, command, args);

    if (command === "RecruitRandomActor") {
      let p = [8, 4, 2, 1], ri = 125;

      if (args[0]) {
        try {
          ri = JSON.parse(args[0]);
        }
        catch (e) {}
      }

      if (args[1]) {
        try {
          p = JSON.parse(args[1]);
        }
        catch (e) {
          try {
            p = args[1].split(",").map(Number);
          }
          catch (e) {}
        }
      }

      const r = cw(p);

      if (!c[r] || c[r].length === 0) {
        $gameMessage.add("ERRORE: NESSUN ATTORE DISPONIBILE IN QUESTA CATEGORIA.");
        return;
      }

      const ci = Math.floor(Math.random() * c[r].length);
      const a = $gameActors.actor(c[r][ci]);

      if ($gameParty.members().includes(a)) {
        $gameMessage.add(`${a.name()} è già nel gruppo.\n${a.name()} guadagnerà ${ri * a.level} esperienza.\nTi saranno rimborsati ${ri} Dabloons!`);
        $gameParty.gainGold(ri);
        a.gainExp(ri * a.level);
      } else {
        $gameParty.addActor(a.actorId());
        const e = ["Uhh", "Nice", "Pazzesco", "No vabbè"][r];
        $gameMessage.add(`${e}, hai sbloccato ${a.name()}!`);
      }
    }
  };
})();