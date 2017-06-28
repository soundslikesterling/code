//Delay line class with multiple taps

//#include stdint / types

//Max buffer length (max allowable)
//buffer length
//write head pointer
//read head pointer

//tap (subclass)
//read_block(start_point, end_point, rate, wrap_bool)

namespace delay_line {

class Buffer{
	public:
		Buffer(buffer_length, MAX_BUFFER_SIZE);
		~Buffer();
		uint32_t get_length();  //Get Length of buffer N
		size_t get_type(); 		//Get Size of elements (char, int, long, float)
		uint32_t fill_level();	//How much space is used in the buffer
		uint32_t resize(uint32_t new_length);	//resize the buffer, return success (0) or failure 
				//TODO should this handle non-contiguous blocks? 
		void flush();			//dump existing un-read data
		void reset();			//set read and write head to 0
	private:
	//Buffer Properties: Length N, element size X, max size M
		static const uint32_t MAX_BUFFER_SIZE; //TODO pass whatever the max memory size is. Depends on where it's stored and the type
		uint32_t buffer_length;					//this should be adjustable at anytime
		uint32_t buffer[buffer_length];
		uint32_t write_index;
		uint32_t read_index;
		//some kind of error state or enum (read overrun, write overflow, etc)
		void write_data(uint32_t);		//write to current location
		uint32_t read_data(uint32_t);	//read from location
}

class ReadHead{
	public:
		ReadHead(Output*);
		~ReadHead();

		void do_read();		//read just 1 element to the output sink
		void do_read(uint32_t);		//read n elements to the output sink
		uint32_t return_read();		//read and return an element (bypass sink)
		uint32_t* return_read(uint32_t);	//read and return a block of elements (bypass sink)
		uint32_t get_read_index();
	private:
		uint32_t* output_sink;		//where's the data going
		size_t data_type;
		uint32_t read_index;
		//error state 		
}
class WriteHead{
	public:
		WriteHead(Input*);
		~WriteHead();
		
		void do_write();		//write 1 element from the source this would not apply in a DMA
		void do_write(uint32_t);	//write a chunk of elements
		uint32_t return_write();	//pull and return data from the source
		uint32_t* return_write(uint32_t);
		uint32_t get_write_index();
		
	private:
		uint32_t* input_source;
		size_t data_type;
		uint32_t write_index;
		//error states 
		//write wrap (bool) 
}

class DelayLine{
	public:
		DelayLine(Buffer*, WriteHead*, ReadHead*);
		~DelayLine();
	
	private:
		WriteHead w;
		ReadHead r;		//TODO make this an array for multiple heads
		Buffer b;
		//error states

		uint32_t get_buffer_length();
		Buffer get_buffer();
		WriteHead get_write_head();
		
		ReadHead get_read_head();
		uint32_t add_read_head();
		uint32_t delete_read_head();
		
		//Handle Wraps and overruns 
		
		//TODO add modulation options
		//Need timer or scheduler
		//get_read_speed
		//set_read_speed
		//Handle read/write speed modulation	
		//Incoming write speed
		//Outgoing read speed
	
		//TODO add helper functions
		//samples_to_time        //how of a delay can a certain number of samples produce
		//time_to_samples        //how many samples will be need for a certain delay time
		//samples_to_mem_size //How much memory does x number of samples consume
		//mem_size_to_samples //max allowable buffer size for given element size and available memory
		
}

}