// For FFI and Proxy Pattern, it's best to separate the Rust server code and the C++ client code into separate dynamic libraries. This would make it easier to link the Rust server with the C++ client using FFI. The client application could then dynamically load the Rust library at runtime to make use of its capabilities.

// Compile this Rust code into a dynamic library (librust_server.so).

use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::thread;
extern crate flatbuffers;
pub mod example_generated;
use example_generated::MsgDataTypes::;
#[no_mangle]
pub extern "C" fn handle_client(mut stream: TcpStream) {
    let mut data = [0 as u8; 512]; // using 512 byte buffer
    while match stream.read(&mut data) {
        Ok(size) => {
            let req = flatbuffers::get_root::<MsgDataTypes::Request>(&data);
            // Process the request and prepare a response
            let mut builder = flatbuffers::FlatBufferBuilder::new();
            let msg = builder.create_string("response message");
            let res = MsgDataTypes::Response::create(&mut builder, &MsgDataTypes::ResponseArgs {
                id: req.id(),
                message: Some(msg),
                success: true
            });
            builder.finish(res, None);
            stream.write(builder.finished_data()).unwrap();
            true
        },
        Err(_) => {
            println!("An error occurred, terminating connection with {}", stream.peer_addr().unwrap());
            stream.shutdown(std::net::Shutdown::Both).unwrap();
            false
        }
    } {}
}
#[no_mangle]
pub extern "C" fn start_server() {
    let listener = TcpListener::bind("0.0.0.0:8888").unwrap();
    println!("Server listening on port 8888");
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                println!("New connection: {}", stream.peer_addr().unwrap());
                thread::spawn(move|| {
                    handle_client(stream)
                });
            }
            Err(e) => {
                println!("Error: {}", e);
            }
        }
    }
    drop(listener);
}
// C++ Qt client code
extern "C" {
    void start_server();
    void stop_server();
    void handle_client(void *stream);
  }
