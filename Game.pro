TEMPLATE = subdirs

SUBDIRS += \
	AgentTest \
	course \
	Student

course.subdir = course/Course
Student.depends = course
