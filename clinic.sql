--
-- PostgreSQL database dump
--

-- Dumped from database version 12.18 (Ubuntu 12.18-0ubuntu0.20.04.1)
-- Dumped by pg_dump version 12.18 (Ubuntu 12.18-0ubuntu0.20.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: postgres; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE postgres WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'en_US.UTF-8' LC_CTYPE = 'en_US.UTF-8';


ALTER DATABASE postgres OWNER TO postgres;

\connect postgres

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: DATABASE postgres; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE postgres IS 'default administrative connection database';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: access_level; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.access_level (
    id integer NOT NULL,
    type_role integer,
    role_name text
);


ALTER TABLE public.access_level OWNER TO postgres;

--
-- Name: TABLE access_level; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE public.access_level IS 'Уровни доступа пользователей';


--
-- Name: access_level_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.access_level_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.access_level_id_seq OWNER TO postgres;

--
-- Name: access_level_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.access_level_id_seq OWNED BY public.access_level.id;


--
-- Name: animals_patients; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.animals_patients (
    id integer NOT NULL,
    user_id integer,
    animal_type_id integer,
    name text,
    sympthom text
);


ALTER TABLE public.animals_patients OWNER TO postgres;

--
-- Name: animals_patients_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.animals_patients_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.animals_patients_id_seq OWNER TO postgres;

--
-- Name: animals_patients_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.animals_patients_id_seq OWNED BY public.animals_patients.id;


--
-- Name: appointments; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.appointments (
    id integer NOT NULL,
    animal_id integer,
    doctor_id integer,
    date timestamp without time zone
);


ALTER TABLE public.appointments OWNER TO postgres;

--
-- Name: appointments_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.appointments_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.appointments_id_seq OWNER TO postgres;

--
-- Name: appointments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.appointments_id_seq OWNED BY public.appointments.id;


--
-- Name: cabinets; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.cabinets (
    id integer NOT NULL,
    cabinet_number integer,
    cabinet_name text
);


ALTER TABLE public.cabinets OWNER TO postgres;

--
-- Name: cabinets_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.cabinets_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cabinets_id_seq OWNER TO postgres;

--
-- Name: cabinets_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.cabinets_id_seq OWNED BY public.cabinets.id;


--
-- Name: doctors; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.doctors (
    id integer NOT NULL,
    user_id integer,
    cabinet_id integer,
    post_id integer
);


ALTER TABLE public.doctors OWNER TO postgres;

--
-- Name: doctors_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.doctors_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.doctors_id_seq OWNER TO postgres;

--
-- Name: doctors_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.doctors_id_seq OWNED BY public.doctors.id;


--
-- Name: kind_animals; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.kind_animals (
    id integer NOT NULL,
    animal_type text NOT NULL
);


ALTER TABLE public.kind_animals OWNER TO postgres;

--
-- Name: TABLE kind_animals; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE public.kind_animals IS 'Таблица видов животных';


--
-- Name: kind_animals_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.kind_animals_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.kind_animals_id_seq OWNER TO postgres;

--
-- Name: kind_animals_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.kind_animals_id_seq OWNED BY public.kind_animals.id;


--
-- Name: post_type; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.post_type (
    id integer NOT NULL,
    post_type text
);


ALTER TABLE public.post_type OWNER TO postgres;

--
-- Name: TABLE post_type; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE public.post_type IS 'Таблица видов должностей';


--
-- Name: post_type_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.post_type_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.post_type_id_seq OWNER TO postgres;

--
-- Name: post_type_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.post_type_id_seq OWNED BY public.post_type.id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    name text,
    surname text,
    patronymic text,
    age integer,
    telephone text,
    login text,
    password text,
    access_level_id integer
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.users ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.users_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: visits; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.visits (
    id integer NOT NULL,
    appointment_id integer,
    dyagnosis text
);


ALTER TABLE public.visits OWNER TO postgres;

--
-- Name: visits_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.visits_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.visits_id_seq OWNER TO postgres;

--
-- Name: visits_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.visits_id_seq OWNED BY public.visits.id;


--
-- Name: access_level id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.access_level ALTER COLUMN id SET DEFAULT nextval('public.access_level_id_seq'::regclass);


--
-- Name: animals_patients id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.animals_patients ALTER COLUMN id SET DEFAULT nextval('public.animals_patients_id_seq'::regclass);


--
-- Name: appointments id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.appointments ALTER COLUMN id SET DEFAULT nextval('public.appointments_id_seq'::regclass);


--
-- Name: cabinets id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cabinets ALTER COLUMN id SET DEFAULT nextval('public.cabinets_id_seq'::regclass);


--
-- Name: doctors id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.doctors ALTER COLUMN id SET DEFAULT nextval('public.doctors_id_seq'::regclass);


--
-- Name: kind_animals id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.kind_animals ALTER COLUMN id SET DEFAULT nextval('public.kind_animals_id_seq'::regclass);


--
-- Name: post_type id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.post_type ALTER COLUMN id SET DEFAULT nextval('public.post_type_id_seq'::regclass);


--
-- Name: visits id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.visits ALTER COLUMN id SET DEFAULT nextval('public.visits_id_seq'::regclass);


--
-- Data for Name: access_level; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.access_level (id, type_role, role_name) FROM stdin;
1	1	Пациент
2	2	Доктор
3	3	Регистратура
\.


--
-- Data for Name: animals_patients; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.animals_patients (id, user_id, animal_type_id, name, sympthom) FROM stdin;
1	1	1	Пеппа	Разрыв прямой кишки
2	1	1	Кошка	Кишечное расстройство
3	2	3	Руи	Отёк левого уха
5	1	1	DOMEKANO	Болит живот
\.


--
-- Data for Name: appointments; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.appointments (id, animal_id, doctor_id, date) FROM stdin;
\.


--
-- Data for Name: cabinets; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.cabinets (id, cabinet_number, cabinet_name) FROM stdin;
1	14	Ветеринар
2	15	Ветеринар-онколог
3	16	Ветеринар-проктолог
4	19	Ветеринар-хирург
5	20	Ветеринар-терапевт
6	21	Ветеринар-онколог
7	22	Ветеринар-онколог
8	23	Ветеринар-хирург
9	24	Ветеринар-хирург
\.


--
-- Data for Name: doctors; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.doctors (id, user_id, cabinet_id, post_id) FROM stdin;
1	3	1	1
2	4	2	2
3	5	4	3
\.


--
-- Data for Name: kind_animals; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.kind_animals (id, animal_type) FROM stdin;
1	Кошка
2	Собака
3	Крыса
\.


--
-- Data for Name: post_type; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.post_type (id, post_type) FROM stdin;
1	Ветеринар
2	Ветеринар-онколог
3	Ветеринар-хирург
4	Ветеринар-терапевт
5	Ветеринар-проктолог
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, name, surname, patronymic, age, telephone, login, password, access_level_id) FROM stdin;
3	Егор	Битюков	Дмитриевич	40	+79276215297	Bitukov	qwe	2
4	Станислав	Шашников	Родиславович	45	+78244215297	Shasnikov	qwe1	2
5	Ильнар	Хайруллин	Альбертович	37	+74244215297	Khairullin	qwe2	2
1	Дмитрий	Зубарев	Александрович	20	+7927944951	Zubarev	1	1
2	Антон	Гончаров	Николаевич	25	+79276215291	Goncharov	2	1
6	Екатерина	Абрамова	Вадимовна	28	+79278299878	Abramova	3	3
7	Максим	Цызыров	Сергеевич	23	+74848481841	Cesar	1	1
\.


--
-- Data for Name: visits; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.visits (id, appointment_id, dyagnosis) FROM stdin;
\.


--
-- Name: access_level_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.access_level_id_seq', 3, true);


--
-- Name: animals_patients_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.animals_patients_id_seq', 5, true);


--
-- Name: appointments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.appointments_id_seq', 42, true);


--
-- Name: cabinets_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.cabinets_id_seq', 9, true);


--
-- Name: doctors_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.doctors_id_seq', 3, true);


--
-- Name: kind_animals_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.kind_animals_id_seq', 3, true);


--
-- Name: post_type_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.post_type_id_seq', 5, true);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 7, true);


--
-- Name: visits_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.visits_id_seq', 1, false);


--
-- Name: access_level access_level_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.access_level
    ADD CONSTRAINT access_level_pkey PRIMARY KEY (id);


--
-- Name: animals_patients animals_patients_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.animals_patients
    ADD CONSTRAINT animals_patients_pkey PRIMARY KEY (id);


--
-- Name: appointments appointments_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.appointments
    ADD CONSTRAINT appointments_pkey PRIMARY KEY (id);


--
-- Name: cabinets cabinets_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cabinets
    ADD CONSTRAINT cabinets_pkey PRIMARY KEY (id);


--
-- Name: doctors doctors_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.doctors
    ADD CONSTRAINT doctors_pkey PRIMARY KEY (id);


--
-- Name: kind_animals kind_animals_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.kind_animals
    ADD CONSTRAINT kind_animals_pkey PRIMARY KEY (id);


--
-- Name: post_type post_type_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.post_type
    ADD CONSTRAINT post_type_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: visits visits_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.visits
    ADD CONSTRAINT visits_pkey PRIMARY KEY (id);


--
-- Name: appointments appointments_animal_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.appointments
    ADD CONSTRAINT appointments_animal_id_fkey FOREIGN KEY (animal_id) REFERENCES public.animals_patients(id) NOT VALID;


--
-- Name: appointments appointments_doctor_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.appointments
    ADD CONSTRAINT appointments_doctor_id_fkey FOREIGN KEY (doctor_id) REFERENCES public.doctors(id) NOT VALID;


--
-- Name: doctors doctors_cabinet_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.doctors
    ADD CONSTRAINT doctors_cabinet_id_fkey FOREIGN KEY (cabinet_id) REFERENCES public.cabinets(id) NOT VALID;


--
-- Name: doctors doctors_post_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.doctors
    ADD CONSTRAINT doctors_post_id_fkey FOREIGN KEY (post_id) REFERENCES public.post_type(id) NOT VALID;


--
-- Name: doctors doctors_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.doctors
    ADD CONSTRAINT doctors_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.users(id);


--
-- Name: users users_access_level_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_access_level_id_fkey FOREIGN KEY (access_level_id) REFERENCES public.access_level(id);


--
-- Name: visits visits_appointment_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.visits
    ADD CONSTRAINT visits_appointment_id_fkey FOREIGN KEY (appointment_id) REFERENCES public.appointments(id);


--
-- PostgreSQL database dump complete
--

