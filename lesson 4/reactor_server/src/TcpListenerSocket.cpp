#include "TcpListenerSocket.h"
#include "TcpSocket.h"
#include "EventHandler.h"
#include "Dispatcher.h"

TcpListenerSocket::TcpListenerSocket():
	TcpSocket()
{

}

TcpListenerSocket::~TcpListenerSocket( )
{

}

int32_t TcpListenerSocket::handle_event( uint32_t flags )
{
	// new connection
	if ( flags & EPOLLIN )
	{
		for(;; )
		{
			TcpSocket tcpSocket = this->accept(NonBlocking );
			if ( tcpSocket.fSocket == -1 )
				break;

			printf( "accept connection from %s:%d\n",
					tcpSocket.ip( ).c_str( ),
					tcpSocket.port( ) );

			TcpSession* tcpSession = new TcpSession( tcpSocket );
			sTcpSessionArry.push_back( tcpSession );

			tcpSession->request_event( EPOLLIN | EPOLLET );
		}
	}

	return 0;
}

// void TcpListenerSocket::request_event( int events )
// {
// 
// 	struct epoll_event ev;
// 	ev.events = EPOLLIN | EPOLLET;
// 	ev.data.fd = this->fSocket;
// 	EventHandler *handler = new EventHandler( ev, this );
// 	Dispatcher::register_handler( this->fSocket, handler );
// }

