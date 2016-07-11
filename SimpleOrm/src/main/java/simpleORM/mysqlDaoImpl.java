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
	 * @see simpleORM.mysqlDao#add(java.lang.Object) 增加數據操作
	 * 
	 * @param T:數據庫表中數據對應的對象
	 */
	public void add(T t) throws Exception {
		Class<?> clazz = t.getClass();
		// 獲得表名称
		String tableName = getTableName(clazz);
		StringBuilder fieldNames = new StringBuilder();
		// 获得对象域中对应的数据，设置prepareStatement的时候需要用到
		List<Object> fieldValues = new ArrayList<Object>();
		StringBuilder fieldPlaceHolder = new StringBuilder();
		Field[] fields = clazz.getDeclaredFields();
		PropertyDescriptor propertyDescriptor = null;
		for (Field field : fields) {
			// 用于获取对象中对应的域的值
			propertyDescriptor = new PropertyDescriptor(field.getName(),
					t.getClass());
			// 下面这个是主键列
			if (field.isAnnotationPresent(Id.class)) {
				fieldNames.append(field.getAnnotation(Id.class).value())
						.append(",");
				System.out
						.println(propertyDescriptor.getReadMethod().invoke(t));
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
			} else if (field.isAnnotationPresent(Column.class)) {// 非主键列
				fieldNames.append(field.getAnnotation(Column.class).value())
						.append(",");
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
			} else
				throw new ColumnNotFoundException("数据表中未找到对应的列");
			fieldPlaceHolder.append("? ,");
		}
		// 删除最后多余的,
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
				+ " 插入成功！");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#update(java.lang.Object) 更新操作 param t:对象T，用于更新的数据
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
		// 用于获得类中对应的域的对应的值
		PropertyDescriptor propertyDescriptor = null;
		for (Field field : fields) {
			propertyDescriptor = new PropertyDescriptor(field.getName(),
					t.getClass());
			// 主键域
			if (field.isAnnotationPresent(Id.class)) {
				id = field.getAnnotation(Id.class).value();
				idObj = propertyDescriptor.getReadMethod().invoke(t);

			}
			// 下面是其他域
			else if (field.isAnnotationPresent(Column.class)) {
				fieldNames.add(field.getAnnotation(Column.class).value());
				fieldValues.add(propertyDescriptor.getReadMethod().invoke(t));
				fieldPlaceholders.add("?"); // 注意这里不需要加上逗号
			} else
				throw new ColumnNotFoundException("数据表中未找到对应的列");
		}

		// 由于update语句的id对应的只应该是最后一个，所以应该add到最后面
		fieldValues.add(idObj);
		StringBuilder sql = new StringBuilder();
		sql.append("update ").append(tableName).append(" set ");
		for (int i = 0; i < fieldNames.size(); ++i) {
			sql.append(fieldNames.get(i)).append("=")
					.append(fieldPlaceholders.get(i)).append(",");
		}
		// 删除最后多余的逗号
		sql.deleteCharAt(sql.length() - 1);
		// 拼接sql语句
		sql.append(" where ").append(id).append(" = ?");
		System.out.println(sql);
		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql.toString());
		setPsParameter(fieldValues, pstmt, false);
		pstmt.execute();
		JdbcUtils.releaseResource(pstmt, null);
		System.out.println("sql: " + "\n" + clazz.getSimpleName() + " 更新成功！");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#delete(java.lang.Object, java.lang.Class) param
	 * id:想删除的列的主键的值 clazz: 表对应的类的class
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
			throw new IdNotFoundException("未找到对象对应的Id");

		StringBuilder sql = new StringBuilder();
		sql.append("delete from ").append(tableName).append(" where ")
				.append(Id).append(" = ?");
		System.out.println(sql.toString());
		PreparedStatement pstmt = JdbcUtils.getConnection().prepareStatement(
				sql.toString());
		setPsParameter(fieldValues, pstmt, false);
		pstmt.execute();
		JdbcUtils.releaseResource(pstmt, null);
		System.out.println("sql: " + "\n" + clazz.getSimpleName() + "删除成功！ ");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#select(java.lang.Object, java.lang.Class) param
	 * id : 希望获取的object在数据库中的主键值 param clazz: 对应的class的class属性 return T : 返回的对象
	 */
	public T select(Object id, Class<?> clazz) throws Exception {
		String tableName = getTableName(clazz);
		List<Object> fieldValues = new ArrayList<Object>();
		List<T> resObject = null;
		fieldValues.add(id);

		Map<String, Object> sqlMapper = new HashMap<String, Object>();

		String IdColumn = new String();
		Field[] fields = clazz.getDeclaredFields();
		// Id主要是为了获取where子句所用
		for (Field field : fields) {
			if (field.isAnnotationPresent(Id.class)) {
				IdColumn = field.getAnnotation(Id.class).value();
			}
		}
		if (IdColumn == null)
			throw new IdNotFoundException("未找到对象对应的Id!");

		// 设置主键以及其对应的值
		sqlMapper.put(IdColumn, id);
		// 绑定所有的列名称以及对应的域值
		resObject = selectAll(sqlMapper, clazz);

		System.out.println("sql: " + "\n" + clazz.getSimpleName() + "获取成功！ ");

		return resObject.size() > 0 ? resObject.get(0) : null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see simpleORM.mysqlDao#selectAll(java.util.Map, java.lang.Class) param
	 * sqlMap:Id以及对应的值 param clazz：类对应class return List<T> :返回的对象的所有属性的集合
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
			// 获取对应的Id的名称
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
		// 删除最后多余的,
		fieldNames.deleteCharAt(fieldNames.length() - 1);
		String sql = "select " + fieldNames + " from " + tableName;
		System.out.println(sql);
		// 根据sqlMap中的内容设置特定的where子句，
		// 如果sqlMap中存在id,以及name,那么就设置where id = ?, name = ?
		List<Object> whereValues = new ArrayList<Object>();
		if (sqlMap != null) {
			List<Object> tmpValues = getWhereValues(sqlMap);
			if (tmpValues != null) {
				// where语句,加上之后这个语句就变成完成的sql语句了。
				sql += (String) tmpValues.get(0);
				// 这个tmpValues里面的值位置0是sql语句，类似， where id = ? and name = ? ...
				// 然后第二个位置的值是sql中各个占位符对应的对象的值
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
			// 通过返回的rset中的值来创建新的对象
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
	 * 通过对象list来初始化对象
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
			// 调用写方法来向对象中写数据
			preDescriptor.getWriteMethod().invoke(object, fieldValue);
		}
	}

	/*
	 * 获得
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
	 * 设置preparestatement的对应的占位符的值
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
	 * 获得where子句以及子句中对应的值 param sqlMapper : select选项的类型以及对应的值 return :
	 * fieldValues:fieldValues[0]中是返回的where子句，类似 where id = ? and name = ?
	 * fieldValue[1]中是返回的where子句对应的值
	 */
	private List<Object> getWhereValues(Map<String, Object> sqlMapper) {
		List<Object> fieldValues = new ArrayList<Object>();
		StringBuilder sqlPlaceHolders = new StringBuilder(" where ");
		List<Object> result = new ArrayList<Object>();
		Set<Entry<String, Object>> mapEntrys = sqlMapper.entrySet();
		for (Entry<String, Object> entry : mapEntrys) {
			fieldValues.add(entry.getValue());
			Object value = entry.getValue();
			if (value.getClass() == String.class) // 分出String主要是为了使用通配符
				sqlPlaceHolders.append(entry.getKey()).append(" like ? and ");
			else
				sqlPlaceHolders.append(entry.getKey()).append(" = ? and ");
		}
		// 删除最后一个and语句
		sqlPlaceHolders.delete(sqlPlaceHolders.lastIndexOf("and"),
				sqlPlaceHolders.length());
		result.add(sqlPlaceHolders.toString());
		result.add(fieldValues);
		return result;
	}
}
