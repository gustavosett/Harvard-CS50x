-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28 AND month = 7 AND year = 2021;

SELECT transcript FROM interviews WHERE transcript LIKE "%bakery%" AND day = 28 AND month = 7 AND year = 2021;

SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE passengers.flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2021 AND (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute);

SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute);

SELECT name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE activity = "exit" AND minute >= 15 AND minute <= 25 AND hour = 10 AND day = 28 AND month = 7 AND year = 2021;

SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE transaction_type = "withdraw" AND atm_location = "Leggett Street" AND day = 28 AND month = 7 AND year = 2021;

SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE duration < 60 AND day = 28 AND month = 7 AND year = 2021;

SELECT phone_number FROM people WHERE name = "Bruce";

SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND duration < 60 AND day = 28 AND month = 7 AND year = 2021);