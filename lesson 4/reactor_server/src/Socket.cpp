#include "Socket.h"
#include "EventHandler.h"
#include "Dispatcher.h"

uint32_t Socket::s_num_sockets = 0;

// Socket::Socket()
// {
//     this->s_num_sockets++;
//     if (this->s_num_sockets == 1)
//     {
//         WSADATA wsaData;
//         if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//             printf("WSAStartup error!\n");
//     }
// 
//     this->fSocketType = SOCK_STREAM;
//     this->fProtocol = IPPROTO_TCP;
//     this->fOpened = false;
//     this->fBinded = false;
//     this->fIOType = Blocking;
//     this->open();
//     this->setIOType(this->fIOType);
//     ::setsockopt(this->fSocket, SOL_SOCKET, SO_SNDBUF, (char*)&SEND_BUF_SIZE, sizeof(int));
//     ::setsockopt(this->fSocket, SOL_SOCKET, SO_RCVBUF, (char*)&RECV_BUF_SIZE, sizeof(int));
// }


Socket::Socket( int32_t inSocketType, int32_t inProtocol, IOType inIOType )
{
	this->s_num_sockets++;
	if ( this->s_num_sockets == 1 )
	{
#ifdef WIN32
		WSADATA wsaData;
		if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
			printf( "WSAStartup error!\n" );
#endif
	}

	this->fSocketType = inSocketType;
	this->fProtocol = inProtocol;
	this->fOpened = false;
	this->fBinded = false;
	this->fIOType = inIOType;
	this->open( );
	this->setIOType( this->fIOType );
	::setsockopt( this->fSocket, SOL_SOCKET, SO_SNDBUF, ( char* ) &SEND_BUF_SIZE, sizeof( int ) );
	::setsockopt( this->fSocket, SOL_SOCKET, SO_RCVBUF, ( char* ) &RECV_BUF_SIZE, sizeof( int ) );
}

Socket::~Socket( )
{
	this->s_num_sockets--;
	if ( this->s_num_sockets == 0 )
	{
#ifdef WIN32
		WSACleanup( );
		printf( "clean up all sockets!\n" );
#endif
	}
}

void Socket::open( )
{
	if ( this->fOpened )
	{
		printf( "Already opened!\n" );
		return;
	}

	if ( ( this->fSocket = ::socket( AF_INET, this->fSocketType, this->fProtocol ) ) == -1 )
	{
		printf( "Create socket error!\n" );
		return;
	}
	this->fOpened = true;
}

void Socket::close( )
{
	if ( this->fOpened )
	{
		::close( this->fSocket );
		this->fOpened = false;
		this->fBinded = false;
	}
}

void Socket::bind_to_port( const uint16_t& inPort )
{
	if ( !this->fOpened )
		this->open( );
	else
	{
		if ( this->fBinded )
		{
			printf( "Socket %u already binded!\n", this->fSocket );
			return;
		}

		Address address( inPort );
		if ( bind( this->fSocket, ( const sockaddr* ) &address, sizeof( struct sockaddr ) ) == -1 )
		{
			printf( "Binded socket error!\n" );
			return;
		}
		this->fBinded = true;
	}
}

void Socket::setIOType( IOType inIOType )
{
	int flags = fcntl( this->fSocket, F_GETFL, 0 );
	switch ( inIOType )
	{
	case Blocking:
		if ( flags & O_NONBLOCK )
		{
			flags &= ~O_NONBLOCK;
			fcntl( this->fSocket, F_SETFL, flags );
		}
		break;
	case NonBlocking:
		if ( !( flags & O_NONBLOCK ) )
		{
			flags |= O_NONBLOCK;
			fcntl( this->fSocket, F_SETFL, flags );
		}
		break;
	default:
		printf( "ERROR: No such IO type!\n" );
		break;
	}
	this->fIOType = inIOType;
}

void Socket::reuse_addr( )
{
	int one = 1;
	if ( ::setsockopt( this->fSocket, SOL_SOCKET, SO_REUSEADDR, ( char* ) &one, sizeof( int ) ) == -1 )
	{
		printf( "[reuse_addr] error!\n" );
		return;
	}
	return;
}

void Socket::no_delay( )
{
	int one = 1;
	if ( ::setsockopt( this->fSocket, IPPROTO_TCP, TCP_NODELAY, ( char* ) &one, sizeof( int ) ) == -1 )
	{
		printf( "[no_delay] error!\n" );
		return;
	}
	return;
}

void Socket::keep_alive( )
{
	int one = 1;
	if ( ::setsockopt( this->fSocket, SOL_SOCKET, SO_KEEPALIVE, ( char* ) &one, sizeof( int ) ) == -1 )
	{
		printf( "[keep_alive] error!\n" );
		return;
	}
	return;
}

void Socket::set_socket_sndbuf_size( uint32_t inNewSize )
{
	int bufSize = inNewSize;
	if ( ::setsockopt( this->fSocket, SOL_SOCKET, SO_SNDBUF, ( char* ) &bufSize, sizeof( int ) ) == -1 )
	{
		printf( "[set_socket_sndbuf_size] error!\n" );
		return;
	}
	return;
}

void Socket::set_socket_rcvbuf_size( uint32_t inNewSize )
{
	int bufSize = inNewSize;
	if ( ::setsockopt( this->fSocket, SOL_SOCKET, SO_RCVBUF, ( char* ) &bufSize, sizeof( int ) ) == -1 )
	{
		printf( "[set_socket_rcvbuf_size] error!\n" );
		return;
	}
	return;
}
