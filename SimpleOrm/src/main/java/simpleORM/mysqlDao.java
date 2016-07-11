package simpleORM;

import java.util.List;
import java.util.Map;

/*
 * �����캆�ε�crud����
 */
public interface mysqlDao<T> {

	// ���픵��
	public void add(T t) throws Exception;

	// ������
	public void update(T t) throws Exception;

	// �h������
	public void delete(Object id, Class<?> clazz) throws Exception;

	// �x�񔵓�
	public T select(Object id, Class<?> clazz) throws Exception;

	// select�Ĺ�������H���@����select���}�s�汾�����̎������where��Ϣ
	// ���� select book_id as id, book_name as name where id = ?, name = ?
	public List<T> selectAll(Map<String, Object> sqlMap, Class<?> clazz)
			throws Exception;
}
