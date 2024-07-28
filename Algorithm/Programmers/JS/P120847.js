/** 최댓값 만들기 (1)
 * 정수 배열 numbers가 매개변수로 주어집니다. 
 * numbers의 원소 중 두 개를 곱해 만들 수 있는 최댓값을 return하도록 solution 함수를 완성해주세요.
 */
function solution(numbers) {
    const newNumbers=numbers.sort((a,b)=>b-a);
    return newNumbers[0]*newNumbers[1];
}