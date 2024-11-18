SELECT 
    last_name AS nazwisko, 
    salary AS wynagrodzenie
FROM 
    employees
WHERE 
    department_id IN (20, 50) AND 
    salary BETWEEN 2000 AND 7000
ORDER BY 
    last_name;


-- Kolumna podana przez użytkownika, np. email
SELECT 
    hire_date, 
    last_name AS nazwisko, 
    email -- zastąp „email” inną kolumną, jeśli użytkownik poda inną
FROM 
    employees
WHERE 
    manager_id IS NOT NULL AND 
    EXTRACT(YEAR FROM hire_date) = 2005
ORDER BY 
    email; -- zastąp „email” kolumną podaną przez użytkownika



-- Użytkownik podaje część imienia, np. 'Joh'
SELECT 
    first_name || ' ' || last_name AS pełne_imie_nazwisko, 
    salary AS zarobki, 
    phone_number AS numer_telefonu
FROM 
    employees
WHERE 
    SUBSTR(last_name, 3, 1) = 'e' AND 
    first_name LIKE '%Joh%' -- zmień „Joh” na część imienia podaną przez użytkownika
ORDER BY 
    pełne_imie_nazwisko DESC, 
    salary ASC;


SELECT 
    first_name AS imię, 
    last_name AS nazwisko, 
    ROUND(MONTHS_BETWEEN(SYSDATE, hire_date)) AS liczba_miesięcy,
    CASE 
        WHEN ROUND(MONTHS_BETWEEN(SYSDATE, hire_date)) <= 150 THEN salary * 0.1
        WHEN ROUND(MONTHS_BETWEEN(SYSDATE, hire_date)) BETWEEN 151 AND 200 THEN salary * 0.2
        ELSE salary * 0.3
    END AS wysokość_dodatku
FROM 
    employees
ORDER BY 
    liczba_miesięcy;


SELECT 
    department_id AS dział_id,
    ROUND(SUM(salary)) AS suma_zarobków,
    ROUND(AVG(salary)) AS średnia_zarobków
FROM 
    employees
WHERE 
    salary > 5000
GROUP BY 
    department_id;



SELECT 
    e.last_name AS nazwisko, 
    e.department_id AS numer_departamentu, 
    d.department_name AS nazwa_departamentu, 
    e.job_id AS id_pracy
FROM 
    employees e
JOIN 
    departments d ON e.department_id = d.department_id
WHERE 
    d.location_id = (SELECT location_id FROM locations WHERE city = 'Toronto');
