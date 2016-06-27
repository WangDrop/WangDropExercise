package prodcons;

import redis.clients.jedis.Jedis;

public class TestPub {
	public static void main(String [] args){
		Jedis jedis = new Jedis("127.0.0.1");
		try{
			jedis.publish("channel", "Kode leave nba!");
		}catch(Exception e){
			e.printStackTrace();
		}
		jedis.close();
	}
}
