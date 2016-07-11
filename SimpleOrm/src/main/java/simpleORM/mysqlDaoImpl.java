package simpleORM;

import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import com.wc.annotation.Column;
import com.wc.annotation.Entity;
import com.wc.annotation.Id;
import com.wc.simpleORM.exception.ColumnNotFoundException;
import com.wc.simpleORM.exception.IdNotFoundException;

public class mysqlDaoImpl<T> implements mysqlDao<T> {

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#add(java.lang.Object) ���Ӕ�������
	 * 
	 * @param T:��������Д��������Č���
	 */
	public void add(T t) throws Exception {
		Class<?> clazz = t.getClass();
		// �@�ñ�����
		String tableName = getTableName(clazz);
		StringBuilder fieldNames = new StringBuilder();
		// ��ö������ж�Ӧ�����ݣ�����prepareStatement��ʱ����Ҫ�õ�
		List<Object> fieldValues = new ArrayList<Object>();
		StringBuilder fieldPlaceHolder = new StringBuilder();
		Field[] fields = clazz.getDeclaredFields();
		PropertyDescriptor propertyDescriptor = null;
		for (Field field : fields) {
			// ���ڻ�ȡ�����ж�Ӧ�����ֵ
			propertyDescriptor = new PropertyDescriptor(field.getName(),
					t.getClass());
			// ���������������
			if (field.isAnnotationPresent(Id.class)) {
				fieldNames.append(field.getAnnotation(Id.class).value())
						.append(",");
				System.out
						.println(propertyDescriptor.getReadMethod().invoke(t));
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
			} else if (field.isAnnotationPresent(Column.class)) {// ��������
				fieldNames.append(field.getAnnotation(Column.class).value())
						.append(",");
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
			} else
				throw new ColumnNotFoundException("���ݱ���δ�ҵ���Ӧ����");
			fieldPlaceHolder.append("? ,");
		}
		// ɾ���������,
		fieldNames.deleteCharAt(fieldNames.length() - 1);
		fieldPlaceHolder.deleteCharAt(fieldPlaceHolder.length() - 1);
		StringBuilder sql = new StringBuilder();
		sql.append(" insert into ").append(tableName).append(" (")
				.append(fieldNames).append(") VALUES( ")
				.append(fieldPlaceHolder).append(")");
		System.out.println(sql);

		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql.toString());
		setPsParameter(fieldValues, pstmt, false);

		pstmt.execute();
		JdbcUtils.releaseResource(pstmt, null);
		System.out.println("sql: " + "\n    " + clazz.getSimpleName()
				+ " ����ɹ���");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#update(java.lang.Object) ���²��� param t:����T�����ڸ��µ�����
	 */
	public void update(T t) throws Exception {
		Class<?> clazz = t.getClass();
		String tableName = getTableName(clazz);
		String id = null;
		Object idObj = null;
		List<String> fieldNames = new ArrayList<String>();
		List<Object> fieldValues = new ArrayList<Object>();
		List<String> fieldPlaceholders = new ArrayList<String>();
		Field[] fields = clazz.getDeclaredFields();
		// ���ڻ�����ж�Ӧ����Ķ�Ӧ��ֵ
		PropertyDescriptor propertyDescriptor = null;
		for (Field field : fields) {
			propertyDescriptor = new PropertyDescriptor(field.getName(),
					t.getClass());
			// ������
			if (field.isAnnotationPresent(Id.class)) {
				id = field.getAnnotation(Id.class).value();
				idObj = propertyDescriptor.getReadMethod().invoke(t);

			}
			// ������������
			else if (field.isAnnotationPresent(Column.class)) {
				fieldNames.add(field.getAnnotation(Column.class).value());
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
				fieldPlaceholders.add("?"); // ע�����ﲻ��Ҫ���϶���
			} else
				throw new ColumnNotFoundException("���ݱ���δ�ҵ���Ӧ����");
		}

		// ����update����id��Ӧ��ֻӦ�������һ��������Ӧ��add�������
		fieldValues.add(idObj);
		StringBuilder sql = new StringBuilder();
		sql.append("update ").append(tableName).append(" set ");
		for (int i = 0; i < fieldNames.size(); ++i) {
			sql.append(fieldNames.get(i)).append("=")
					.append(fieldPlaceholders.get(i)).append(",");
		}
		// ɾ��������Ķ���
		sql.deleteCharAt(sql.length() - 1);
		// ƴ��sql���
		sql.append(" where ").append(id).append(" = ?");
		System.out.println(sql);
		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql.toString());
		setPsParameter(fieldValues, pstmt, false);
		pstmt.execute();
		JdbcUtils.releaseResource(pstmt, null);
		System.out.println("sql: " + "\n" + clazz.getSimpleName() + " ���³ɹ���");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#delete(java.lang.Object, java.lang.Class) param
	 * id:��ɾ�����е�������ֵ clazz: ���Ӧ�����class
	 */
	public void delete(Object id, Class<?> clazz) throws Exception {
		String tableName = getTableName(clazz);
		List<Object> fieldValues = new ArrayList<Object>();
		fieldValues.add(id);
		String Id = new String();
		Field[] fields = clazz.getDeclaredFields();
		for (Field field : fields) {
			if (field.isAnnotationPresent(Id.class)) {
				Id = field.getAnnotation(Id.class).value();
				break;
			}
		}
		if (Id == null)
			throw new IdNotFoundException("δ�ҵ������Ӧ��Id");

		StringBuilder sql = new StringBuilder();
		sql.append("delete from ").append(tableName).append(" where ")
				.append(Id).append(" = ?");
		System.out.println(sql.toString());
		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql.toString());
		setPsParameter(fieldValues, pstmt, false);
		pstmt.execute();
		JdbcUtils.releaseResource(pstmt, null);
		System.out.println("sql: " + "\n" + clazz.getSimpleName() + "ɾ���ɹ��� ");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#select(java.lang.Object, java.lang.Class) param
	 * id : ϣ����ȡ��object�����ݿ��е�����ֵ param clazz: ��Ӧ��class��class���� return T : ���صĶ���
	 */
	public T select(Object id, Class<?> clazz) throws Exception {
		String tableName = getTableName(clazz);
		List<Object> fieldValues = new ArrayList<Object>();
		List<T> resObject = null;
		fieldValues.add(id);

		Map<String, Object> sqlMapper = new HashMap<String, Object>();

		String IdColumn = new String();
		Field[] fields = clazz.getDeclaredFields();
		// Id��Ҫ��Ϊ�˻�ȡwhere�Ӿ�����
		for (Field field : fields) {
			if (field.isAnnotationPresent(Id.class)) {
				IdColumn = field.getAnnotation(Id.class).value();
			}
		}
		if (IdColumn == null)
			throw new IdNotFoundException("δ�ҵ������Ӧ��Id!");

		// ���������Լ����Ӧ��ֵ
		sqlMapper.put(IdColumn, id);
		// �����е��������Լ���Ӧ����ֵ
		resObject = selectAll(sqlMapper, clazz);

		System.out.println("sql: " + "\n" + clazz.getSimpleName() + "��ȡ�ɹ��� ");

		return resObject.size() > 0 ? resObject.get(0) : null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#selectAll(java.util.Map, java.lang.Class) param
	 * sqlMap:Id�Լ���Ӧ��ֵ param clazz�����Ӧclass return List<T> :���صĶ�����������Եļ���
	 */
	public List<T> selectAll(Map<String, Object> sqlMap, Class<?> clazz)
			throws Exception {
		List<T> list = new ArrayList<T>();
		String tableName = getTableName(clazz);
		StringBuilder fieldNames = new StringBuilder();
		String Id;
		String columnName;
		String fieldName = null;
		Field[] fields = clazz.getDeclaredFields();
		for (Field field : fields) {
			fieldName = field.getName();
			// ��ȡ��Ӧ��Id������
			if (field.isAnnotationPresent(Id.class)) {
				Id = field.getAnnotation(Id.class).value();
				fieldNames.append(Id).append(" as ").append(fieldName)
						.append(",");
			} else if (field.isAnnotationPresent(Column.class)) {
				columnName = field.getAnnotation(Column.class).value();
				fieldNames.append(columnName).append(" as ").append(fieldName)
						.append(",");
			}
		}
		// ɾ���������,
		fieldNames.deleteCharAt(fieldNames.length() - 1);
		String sql = "select " + fieldNames + " from " + tableName;
		System.out.println(sql);
		// ����sqlMap�е����������ض���where�Ӿ䣬
		// ���sqlMap�д���id,�Լ�name,��ô������where id = ?, name = ?
		List<Object> whereValues = new ArrayList<Object>();
		if (sqlMap != null) {
			List<Object> tmpValues = getWhereValues(sqlMap);
			if (tmpValues != null) {
				// where���,����֮��������ͱ����ɵ�sql����ˡ�
				sql += (String) tmpValues.get(0);
				// ���tmpValues�����ֵλ��0��sql��䣬���ƣ� where id = ? and name = ? ...
				// Ȼ��ڶ���λ�õ�ֵ��sql�и���ռλ����Ӧ�Ķ����ֵ
				whereValues = (List<Object>) tmpValues.get(1);
			}
		}

		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql);
		if (!whereValues.isEmpty()) {
			setPsParameter(whereValues, pstmt, true);
		}
		ResultSet rs = pstmt.executeQuery();
		while (rs.next()) {
			// ͨ�����ص�rset�е�ֵ�������µĶ���
			T t = (T) clazz.newInstance();
			initObject(t, fields, rs);
			list.add(t);
		}
		System.out.println(list);
		JdbcUtils.releaseResource(pstmt, rs);
		System.out.println(sql);
		return list;
	}

	/*
	 * ͨ������list����ʼ������
	 */
	private void initObject(Object object, Field[] fields, ResultSet resultSet)
			throws SQLException, IntrospectionException,
			IllegalAccessException, IllegalArgumentException,
			InvocationTargetException {
		PropertyDescriptor preDescriptor = null;
		Object fieldValue = null;
		String fieldName = null;
		Class<?> clazz = null;
		for (Field field : fields) {
			clazz = field.getType();
			fieldName = field.getName();
			if (clazz == String.class) {
				fieldValue = resultSet.getString(fieldName);
			} else if (clazz == Integer.class || clazz == int.class) {
				fieldValue = resultSet.getInt(fieldName);
			} else if (clazz == Character.class || clazz == char.class) {
				fieldValue = resultSet.getCharacterStream(fieldName);
			} else if (clazz == Byte.class || clazz == byte.class) {
				fieldValue = resultSet.getByte(fieldName);
			} else if (clazz == Boolean.class || clazz == boolean.class) {
				fieldValue = resultSet.getBoolean(fieldName);
			} else if (clazz == Float.class || clazz == float.class) {
				fieldValue = resultSet.getFloat(fieldName);
			} else if (clazz == Double.class || clazz == double.class) {
				fieldValue = resultSet.getDouble(fieldName);
			} else if (clazz == Short.class || clazz == short.class) {
				fieldValue = resultSet.getShort(fieldName);
			} else if (clazz == Long.class || clazz == long.class) {
				fieldValue = resultSet.getLong(fieldName);
			} else if (clazz == Date.class) {
				fieldValue = resultSet.getDate(fieldName);
			} else if (clazz.isArray()) {
				fieldValue = resultSet.getString(fieldName).split(",");
			}
			preDescriptor = new PropertyDescriptor(fieldName, object.getClass());
			// ����д�������������д����
			preDescriptor.getWriteMethod().invoke(object, fieldValue);
		}
	}

	/*
	 * ���
	 */
	public String getTableName(Class<?> clazz) throws Exception {
		if (clazz.isAnnotationPresent(Entity.class)) {
			Entity entity = clazz.getAnnotation(Entity.class);
			return entity.value();
		} else {
			throw new Exception(clazz.getName() + " is not a Entity type!");
		}
	}

	/*
	 * ����preparestatement�Ķ�Ӧ��ռλ����ֵ
	 */
	@SuppressWarnings("unused")
	private void setPsParameter(List<Object> values, PreparedStatement pstmt,
			boolean isSearch) throws SQLException {
		Object object = null;
		Class<?> clazz = null;
		for (int i = 1; i <= values.size(); ++i) {
			object = values.get(i - 1);
			clazz = object.getClass();
			if (clazz.equals(String.class)) {
				if (isSearch)
					pstmt.setString(i, "%" + (String) object + "%");
				else
					pstmt.setString(i, (String) object);
			} else if (clazz.equals(Boolean.class)
					|| clazz.equals(boolean.class)) {
				pstmt.setBoolean(i, (Boolean) object);
			} else if (clazz.equals(Integer.class)
					|| clazz.equals(Integer.class)) {
				pstmt.setInt(i, (Integer) object);
			} else if (clazz.equals(Byte.class) || clazz.equals(byte.class)) {
				pstmt.setByte(i, (Byte) object);
			} else if (clazz.equals(Character.class)
					|| clazz.equals(char.class)) {
				pstmt.setObject(i, object, Types.CHAR);
			} else if (clazz.equals(Date.class)) {
				pstmt.setDate(i,
						new java.sql.Date(((java.util.Date) object).getTime()));
			} else {
				pstmt.setObject(i, object, Types.NUMERIC); // double or others
			}
		}
	}

	/*
	 * ���where�Ӿ��Լ��Ӿ��ж�Ӧ��ֵ param sqlMapper : selectѡ��������Լ���Ӧ��ֵ return :
	 * fieldValues:fieldValues[0]���Ƿ��ص�where�Ӿ䣬���� where id = ? and name = ?
	 * fieldValue[1]���Ƿ��ص�where�Ӿ��Ӧ��ֵ
	 */
	private List<Object> getWhereValues(Map<String, Object> sqlMapper) {
		List<Object> fieldValues = new ArrayList<Object>();
		StringBuilder sqlPlaceHolders = new StringBuilder(" where ");
		List<Object> result = new ArrayList<Object>();
		Set<Entry<String, Object>> mapEntrys = sqlMapper.entrySet();
		for (Entry<String, Object> entry : mapEntrys) {
			fieldValues.add(entry.getValue());
			Object value = entry.getValue();
			if (value.getClass() == String.class) // �ֳ�String��Ҫ��Ϊ��ʹ��ͨ���
				sqlPlaceHolders.append(entry.getKey()).append(" like ? and ");
			else
				sqlPlaceHolders.append(entry.getKey()).append(" = ? and ");
		}
		// ɾ�����һ��and���
		sqlPlaceHolders.delete(sqlPlaceHolders.lastIndexOf("and"),
				sqlPlaceHolders.length());
		result.add(sqlPlaceHolders.toString());
		result.add(fieldValues);
		return result;
	}
}
