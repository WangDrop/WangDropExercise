package simpleORM;

import java.util.List;
import java.util.Map;

/*
 * 數據庫簡單的crud操作
 */
public interface mysqlDao<T> {

	// 增添數據
	public void add(T t) throws Exception;

	// 更新數據
	public void update(T t) throws Exception;

	// 刪除數據
	public void delete(Object id, Class<?> clazz) throws Exception;

	// 選擇數據
	public T select(Object id, Class<?> clazz) throws Exception;

	// select的工具類，實際上這個是select的複雜版本，用於處理更多的where信息
	// 例如 select book_id as id, book_name as name where id = ?, name = ?
	public List<T> selectAll(Map<String, Object> sqlMap, Class<?> clazz)
			throws Exception;
}
