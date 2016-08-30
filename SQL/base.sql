--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner:
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner:
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: NAMESTRING100; Type: DOMAIN; Schema: public; Owner: rise
--

CREATE DOMAIN "NAMESTRING100" AS character varying(100);


ALTER DOMAIN "NAMESTRING100" OWNER TO rise;

--
-- Name: t_function_count_update(); Type: FUNCTION; Schema: public; Owner: rise
--

CREATE FUNCTION t_function_count_update() RETURNS trigger
    LANGUAGE plpgsql
    AS $$DECLARE
querys varchar(255);

BEGIN
IF TG_OP = 'UPDATE' THEN
UPDATE rise SET archive=true,archivedatetime=NOW();
INSERT INTO rise(
            riseid, menuid, userid, count, archive, archivedatetime, lastupdate,
            deleted)
    VALUES (nextval('"rise_riseId_seq"'::regclass), NEW.menuid, NEW.userid, NEW.count, NULL, NULL,
        NOW(),false);
RETURN NEW;
END IF;
END;$$;


ALTER FUNCTION public.t_function_count_update() OWNER TO rise;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: menu; Type: TABLE; Schema: public; Owner: rise; Tablespace:
--

CREATE TABLE menu (
    menuid integer NOT NULL,
    menuname "NAMESTRING100",
    deleted boolean
);


ALTER TABLE menu OWNER TO rise;

--
-- Name: menu_menuId_seq; Type: SEQUENCE; Schema: public; Owner: rise
--

CREATE SEQUENCE "menu_menuId_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "menu_menuId_seq" OWNER TO rise;

--
-- Name: menu_menuId_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: rise
--

ALTER SEQUENCE "menu_menuId_seq" OWNED BY menu.menuid;


--
-- Name: rise; Type: TABLE; Schema: public; Owner: rise; Tablespace:
--

CREATE TABLE rise (
    riseid integer NOT NULL,
    menuid integer,
    userid integer,
    count numeric(5,2),
    archive boolean,
    archivedatetime timestamp without time zone,
    lastupdate timestamp without time zone,
    deleted boolean
);


ALTER TABLE rise OWNER TO rise;

--
-- Name: rise_riseId_seq; Type: SEQUENCE; Schema: public; Owner: rise
--

CREATE SEQUENCE "rise_riseId_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "rise_riseId_seq" OWNER TO rise;

--
-- Name: rise_riseId_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: rise
--

ALTER SEQUENCE "rise_riseId_seq" OWNED BY rise.riseid;


--
-- Name: users; Type: TABLE; Schema: public; Owner: rise; Tablespace:
--

CREATE TABLE users (
    userid integer NOT NULL,
    username "NAMESTRING100",
    deleted boolean
);


ALTER TABLE users OWNER TO rise;

--
-- Name: users_userId_seq; Type: SEQUENCE; Schema: public; Owner: rise
--

CREATE SEQUENCE "users_userId_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "users_userId_seq" OWNER TO rise;

--
-- Name: users_userId_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: rise
--

ALTER SEQUENCE "users_userId_seq" OWNED BY users.userid;


--
-- Name: menuid; Type: DEFAULT; Schema: public; Owner: rise
--

ALTER TABLE ONLY menu ALTER COLUMN menuid SET DEFAULT nextval('"menu_menuId_seq"'::regclass);


--
-- Name: riseid; Type: DEFAULT; Schema: public; Owner: rise
--

ALTER TABLE ONLY rise ALTER COLUMN riseid SET DEFAULT nextval('"rise_riseId_seq"'::regclass);


--
-- Name: userid; Type: DEFAULT; Schema: public; Owner: rise
--

ALTER TABLE ONLY users ALTER COLUMN userid SET DEFAULT nextval('"users_userId_seq"'::regclass);


--
-- Name: PK_MENUID; Type: CONSTRAINT; Schema: public; Owner: rise; Tablespace:
--

ALTER TABLE ONLY menu
    ADD CONSTRAINT "PK_MENUID" PRIMARY KEY (menuid);


--
-- Name: PK_RISEID; Type: CONSTRAINT; Schema: public; Owner: rise; Tablespace:
--

ALTER TABLE ONLY rise
    ADD CONSTRAINT "PK_RISEID" PRIMARY KEY (riseid);


--
-- Name: PK_USERID; Type: CONSTRAINT; Schema: public; Owner: rise; Tablespace:
--

ALTER TABLE ONLY users
    ADD CONSTRAINT "PK_USERID" PRIMARY KEY (userid);


--
-- Name: t_rise_count_update; Type: TRIGGER; Schema: public; Owner: rise
--

CREATE TRIGGER t_rise_count_update AFTER UPDATE OF count ON rise FOR EACH ROW EXECUTE PROCEDURE t_function_count_update();


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--
