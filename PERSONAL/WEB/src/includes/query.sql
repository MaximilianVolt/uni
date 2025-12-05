SELECT COUNT(N.id), N.topic
FROM News N
JOIN -- Tutte le tabelle necessarie
WHERE N.data = 'DATE-ARGUMENT'
AND N.topic = 'TOPIC-ARGUMENT'
AND N.classificazione = 'FAKE'
GROUP BY N.topic
