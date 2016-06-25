package test.jedisTest;

import java.util.Iterator;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisSentinelPool;

public class JedisUtilTest {
	private Jedis jedis;
	@Before
	public void setUp() throws Exception{
		jedis = new Jedis("127.0.0.1", 6379);
	
	}
	@Test
	public void testString(){
		jedis.set("name", "wangcheng");
		jedis.set("age", "23");
		String username = jedis.get("name");
		String userage = jedis.get("age");
		System.out.println(username + ": " + userage);
		jedis.del("age");
		System.out.println(jedis.get("age"));
	}
	
	@Test
	public void testMap(){
		Map<String, String> user = new HashMap<String, String>();
		user.put("name", "wangcheng");
		user.put("password", "1316");
		user.put("hobby", "basketball");
		jedis.hmset("user", user);
		List<String> list = jedis.hmget("user", "name");
		System.out.println(list);
		jedis.hdel("user", "name");
		System.out.println(jedis.hmget("user", "name"));
		System.out.println(jedis.hlen("user"));
		System.out.println(jedis.hkeys("user"));
		System.out.println(jedis.hvals("user"));
		Iterator<String> iterator = jedis.hkeys("user").iterator();
		while (iterator.hasNext()) {
			System.out.println(iterator.next());
		}
	}
	@Test
	public void testList(){
		jedis.lpush("redis", "spring");	
		jedis.lpush("redis", "struts");
		jedis.lpush("redis", "hibernate");
		System.out.println(jedis.lrange("redis", 0, -1));
	}
	@Test
	public void testSet(){
		jedis.sadd("redisSet", "wangcheng");
		jedis.sadd("redisSet", "Jxiaolun");
		jedis.sadd("redisSet", "Doom");
		System.out.println(jedis.smembers("redisSet"));
		System.out.println(jedis.sismember("redisSet", "Jxiaolun"));
		System.out.println(jedis.srandmember("redisSet"));
		System.out.println(jedis.scard("redisSet"));
		jedis.srem("redisSet", "Jxiaolun");
		System.out.println(jedis.smembers("redisSet"));
	}
	@Test
	public void testZSet(){
		jedis.zadd("myzset", 100, "wangcheng");
		jedis.zadd("myzset", 101, "jxiaolun");
		jedis.zadd("myzset", 102, "wq");
		jedis.zadd("myzset", 103, "dom");
		System.out.println(jedis.zcard("myzset"));
		Set<String> zset1 = jedis.zrange("myzset", 0, -1);
		Set<String> zset2 = jedis.zrangeByScore("myzset", 100, 103);
		for(Object o : zset1){
			System.out.println(o.toString());
		}
		System.out.println("----------------");
		for(Object o : zset2){
			System.out.println(o.toString());
		}
	}
}
