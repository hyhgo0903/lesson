#include <iostream>
// ����Ʈ��ƮŬ��: �ѹ��� ������ Ÿ����

#include "SkeletonWarrior.h"
// �ؾƲ�� �ƴ϶� �ؾ�� ���
#include "Necromancer.h"

using namespace std;

//getter : ������
//setter : ������

int main()
{
	SkeletonWarrior sw;
	// �θ�Ŭ���� �����ڰ� ����.
	
	// �����Ҵ�(Stack�̶� �޸� ������ ����)
	// �����Ϸ� �ܰ� �������� �޸𸮿� ��� ����
	// RunTime���� �޸� ���� �Ұ�

	SkeletonWarrior* sw1 = new SkeletonWarrior;
	// Ÿ��* �������̸� = new Ÿ��;
	// �����Ҵ�(Heap�̶� �޸� ������ ����)
	// ���� << �޸��Ҵ� ��ġ�� ��ƾ��ϱ⶧��
	// �����Ϸ� �ܰ� �� ���̶� ������ �޸� ������
	// RunTime���� �޸� ���� ����,, �������� ��������
	sw1->output(); // ->�̷��� �Ȱ� ��������
	delete sw1; // �޸� ������ ��ȯ�ϴ� ��. �Ҹ��ںҷ���
	
	sw.racePassive();
	sw.Qskill();
	sw.Wskill();


	cout << "\n";

	Necromancer necro;
	// �θ�Ŭ���� �������� �ƿ�ǲ�� ���� ��µȴ�.

	necro.racePassive();
	necro.Qskill();
	necro.Wskill();


	return 0;
}