void
connection_init(conn_t *conn, conf_t *conf)
{
	protocol_init(conn->proto);	
}

void
make_connection(conn_t *conn)
{
	conn->proto->connect(conn->proto);
}

void
make_request(conn_t *conn)
{
	conn->proto->request(conn->proto);
}

void
fetch_response(conn_t *conn, char *buf, int size)
{
	conn->proto->re	
}

void
connection_deinit(conn_t *conn)
{

}
